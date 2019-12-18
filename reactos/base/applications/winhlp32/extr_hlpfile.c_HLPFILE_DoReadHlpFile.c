#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int version; int dsize; unsigned int topic_maplen; int** topic_map; int* topic_end; } ;
typedef  int /*<<< orphan*/  OFSTRUCT ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  TYPE_1__ HLPFILE ;
typedef  scalar_t__ HFILE ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GET_UINT (int*,int) ; 
 scalar_t__ HFILE_ERROR ; 
 int /*<<< orphan*/  HLPFILE_AddPage (TYPE_1__*,int*,int*,int,unsigned int) ; 
 int /*<<< orphan*/  HLPFILE_GetContext (TYPE_1__*) ; 
 int /*<<< orphan*/  HLPFILE_GetKeywords (TYPE_1__*) ; 
 int /*<<< orphan*/  HLPFILE_GetMap (TYPE_1__*) ; 
 int /*<<< orphan*/  HLPFILE_GetTOMap (TYPE_1__*) ; 
 int /*<<< orphan*/  HLPFILE_ReadFileToBuffer (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  HLPFILE_ReadFont (TYPE_1__*) ; 
 int /*<<< orphan*/  HLPFILE_SkipParagraph (TYPE_1__*,int*,int*,unsigned int*) ; 
 int /*<<< orphan*/  HLPFILE_SystemCommands (TYPE_1__*) ; 
 int /*<<< orphan*/  HLPFILE_UncompressLZ77_Phrases (TYPE_1__*) ; 
 int /*<<< orphan*/  HLPFILE_Uncompress_Phrases40 (TYPE_1__*) ; 
 int /*<<< orphan*/  HLPFILE_Uncompress_Topic (TYPE_1__*) ; 
#define  HLP_DISPLAY 131 
#define  HLP_DISPLAY30 130 
#define  HLP_TABLE 129 
#define  HLP_TOPICHDR 128 
 int /*<<< orphan*/  OF_READ ; 
 scalar_t__ OpenFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINE_ERR (char*,int) ; 
 int /*<<< orphan*/  WINE_TRACE (char*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  WINE_WARN (char*) ; 
 int /*<<< orphan*/  _lclose (scalar_t__) ; 
 int* min (int*,int*) ; 

__attribute__((used)) static BOOL HLPFILE_DoReadHlpFile(HLPFILE *hlpfile, LPCSTR lpszPath)
{
    BOOL        ret;
    HFILE       hFile;
    OFSTRUCT    ofs;
    BYTE*       buf;
    DWORD       ref = 0x0C;
    unsigned    index, old_index, offset, len, offs, topicoffset;

    hFile = OpenFile(lpszPath, &ofs, OF_READ);
    if (hFile == HFILE_ERROR) return FALSE;

    ret = HLPFILE_ReadFileToBuffer(hlpfile, hFile);
    _lclose(hFile);
    if (!ret) return FALSE;

    if (!HLPFILE_SystemCommands(hlpfile)) return FALSE;

    if (hlpfile->version <= 16 && !HLPFILE_GetTOMap(hlpfile)) return FALSE;

    /* load phrases support */
    if (!HLPFILE_UncompressLZ77_Phrases(hlpfile))
        HLPFILE_Uncompress_Phrases40(hlpfile);

    if (!HLPFILE_Uncompress_Topic(hlpfile)) return FALSE;
    if (!HLPFILE_ReadFont(hlpfile)) return FALSE;

    old_index = -1;
    offs = 0;
    do
    {
        BYTE*   end;

        if (hlpfile->version <= 16)
        {
            index  = (ref - 0x0C) / hlpfile->dsize;
            offset = (ref - 0x0C) % hlpfile->dsize;
        }
        else
        {
            index  = (ref - 0x0C) >> 14;
            offset = (ref - 0x0C) & 0x3FFF;
        }

        if (hlpfile->version <= 16 && index != old_index && old_index != -1)
        {
            /* we jumped to the next block, adjust pointers */
            ref -= 12;
            offset -= 12;
        }

        WINE_TRACE("ref=%08x => [%u/%u]\n", ref, index, offset);

        if (index >= hlpfile->topic_maplen) {WINE_WARN("maplen\n"); break;}
        buf = hlpfile->topic_map[index] + offset;
        if (buf + 0x15 >= hlpfile->topic_end) {WINE_WARN("extra\n"); break;}
        end = min(buf + GET_UINT(buf, 0), hlpfile->topic_end);
        if (index != old_index) {offs = 0; old_index = index;}

        switch (buf[0x14])
	{
	case HLP_TOPICHDR: /* Topic Header */
            if (hlpfile->version <= 16)
                topicoffset = ref + index * 12;
            else
                topicoffset = index * 0x8000 + offs;
            if (!HLPFILE_AddPage(hlpfile, buf, end, ref, topicoffset)) return FALSE;
            break;

	case HLP_DISPLAY30:
	case HLP_DISPLAY:
	case HLP_TABLE:
            if (!HLPFILE_SkipParagraph(hlpfile, buf, end, &len)) return FALSE;
            offs += len;
            break;

	default:
            WINE_ERR("buf[0x14] = %x\n", buf[0x14]);
	}

        if (hlpfile->version <= 16)
        {
            ref += GET_UINT(buf, 0xc);
            if (GET_UINT(buf, 0xc) == 0)
                break;
        }
        else
            ref = GET_UINT(buf, 0xc);
    } while (ref != 0xffffffff);

    HLPFILE_GetKeywords(hlpfile);
    HLPFILE_GetMap(hlpfile);
    if (hlpfile->version <= 16) return TRUE;
    return HLPFILE_GetContext(hlpfile);
}