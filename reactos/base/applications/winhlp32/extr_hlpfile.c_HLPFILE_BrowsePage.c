#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct RtfData {int allocated; unsigned int font_scale; unsigned int relative; int /*<<< orphan*/  first_link; scalar_t__ char_pos; scalar_t__ char_pos_rel; int /*<<< orphan*/  force_color; int /*<<< orphan*/ * current_link; int /*<<< orphan*/  ptr; int /*<<< orphan*/  data; int /*<<< orphan*/  in_text; } ;
struct TYPE_10__ {int charset; unsigned int numFonts; int version; int dsize; unsigned int topic_maplen; int** topic_map; int* topic_end; TYPE_2__* fonts; } ;
struct TYPE_9__ {int reference; int /*<<< orphan*/  first_link; TYPE_4__* file; } ;
struct TYPE_7__ {int lfPitchAndFamily; int lfCharSet; char* lfFaceName; } ;
struct TYPE_8__ {int /*<<< orphan*/  color; TYPE_1__ LogFont; } ;
typedef  TYPE_3__ HLPFILE_PAGE ;
typedef  TYPE_4__ HLPFILE ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  ANSI_CHARSET 153 
#define  ARABIC_CHARSET 152 
#define  BALTIC_CHARSET 151 
#define  CHINESEBIG5_CHARSET 150 
#define  DEFAULT_CHARSET 149 
#define  EE_CHARSET 148 
 int /*<<< orphan*/  FALSE ; 
#define  FF_DECORATIVE 147 
#define  FF_MODERN 146 
#define  FF_ROMAN 145 
#define  FF_SCRIPT 144 
#define  FF_SWISS 143 
#define  GB2312_CHARSET 142 
 int GET_UINT (int*,int) ; 
#define  GREEK_CHARSET 141 
 int GetBValue (int /*<<< orphan*/ ) ; 
 int GetGValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetRValue (int /*<<< orphan*/ ) ; 
#define  HANGEUL_CHARSET 140 
#define  HEBREW_CHARSET 139 
 int /*<<< orphan*/  HLPFILE_BrowseParagraph (TYPE_3__*,struct RtfData*,int*,int*,unsigned int*) ; 
 int /*<<< orphan*/  HLPFILE_RtfAddControl (struct RtfData*,char*) ; 
#define  HLP_DISPLAY 138 
#define  HLP_DISPLAY30 137 
#define  HLP_TABLE 136 
#define  HLP_TOPICHDR 135 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  JOHAB_CHARSET 134 
#define  MAC_CHARSET 133 
#define  RUSSIAN_CHARSET 132 
#define  SHIFTJIS_CHARSET 131 
#define  THAI_CHARSET 130 
 int /*<<< orphan*/  TRUE ; 
#define  TURKISH_CHARSET 129 
#define  VIETNAMESE_CHARSET 128 
 int /*<<< orphan*/  WINE_ERR (char*,int) ; 
 int /*<<< orphan*/  WINE_FIXME (char*,int) ; 
 int /*<<< orphan*/  WINE_WARN (char*) ; 
 int* min (int*,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

BOOL    HLPFILE_BrowsePage(HLPFILE_PAGE* page, struct RtfData* rd,
                           unsigned font_scale, unsigned relative)
{
    HLPFILE     *hlpfile = page->file;
    BYTE        *buf, *end;
    DWORD       ref = page->reference;
    unsigned    index, old_index = -1, offset, count = 0, offs = 0;
    unsigned    cpg, parlen;
    char        tmp[1024];
    const char* ck = NULL;

    rd->in_text = TRUE;
    rd->data = rd->ptr = HeapAlloc(GetProcessHeap(), 0, rd->allocated = 32768);
    rd->char_pos = 0;
    rd->first_link = rd->current_link = NULL;
    rd->force_color = FALSE;
    rd->font_scale = font_scale;
    rd->relative = relative;
    rd->char_pos_rel = 0;

    switch (hlpfile->charset)
    {
    case DEFAULT_CHARSET:
    case ANSI_CHARSET:          cpg = 1252; break;
    case SHIFTJIS_CHARSET:      cpg = 932; break;
    case HANGEUL_CHARSET:       cpg = 949; break;
    case GB2312_CHARSET:        cpg = 936; break;
    case CHINESEBIG5_CHARSET:   cpg = 950; break;
    case GREEK_CHARSET:         cpg = 1253; break;
    case TURKISH_CHARSET:       cpg = 1254; break;
    case HEBREW_CHARSET:        cpg = 1255; break;
    case ARABIC_CHARSET:        cpg = 1256; break;
    case BALTIC_CHARSET:        cpg = 1257; break;
    case VIETNAMESE_CHARSET:    cpg = 1258; break;
    case RUSSIAN_CHARSET:       cpg = 1251; break;
    case EE_CHARSET:            cpg = 1250; break;
    case THAI_CHARSET:          cpg = 874; break;
    case JOHAB_CHARSET:         cpg = 1361; break;
    case MAC_CHARSET:           ck = "mac"; break;
    default:
        WINE_FIXME("Unsupported charset %u\n", hlpfile->charset);
        cpg = 1252;
    }
    if (ck)
    {
        sprintf(tmp, "{\\rtf1\\%s\\deff0", ck);
        if (!HLPFILE_RtfAddControl(rd, tmp)) return FALSE;
    }
    else
    {
        sprintf(tmp, "{\\rtf1\\ansi\\ansicpg%d\\deff0", cpg);
        if (!HLPFILE_RtfAddControl(rd, tmp)) return FALSE;
    }

    /* generate font table */
    if (!HLPFILE_RtfAddControl(rd, "{\\fonttbl")) return FALSE;
    for (index = 0; index < hlpfile->numFonts; index++)
    {
        const char* family;
        switch (hlpfile->fonts[index].LogFont.lfPitchAndFamily & 0xF0)
        {
        case FF_MODERN:     family = "modern";  break;
        case FF_ROMAN:      family = "roman";   break;
        case FF_SWISS:      family = "swiss";   break;
        case FF_SCRIPT:     family = "script";  break;
        case FF_DECORATIVE: family = "decor";   break;
        default:            family = "nil";     break;
        }
        sprintf(tmp, "{\\f%d\\f%s\\fprq%d\\fcharset%d %s;}",
                index, family,
                hlpfile->fonts[index].LogFont.lfPitchAndFamily & 0x0F,
                hlpfile->fonts[index].LogFont.lfCharSet,
                hlpfile->fonts[index].LogFont.lfFaceName);
        if (!HLPFILE_RtfAddControl(rd, tmp)) return FALSE;
    }
    if (!HLPFILE_RtfAddControl(rd, "}")) return FALSE;
    /* generate color table */
    if (!HLPFILE_RtfAddControl(rd, "{\\colortbl ;\\red0\\green128\\blue0;")) return FALSE;
    for (index = 0; index < hlpfile->numFonts; index++)
    {
        sprintf(tmp, "\\red%d\\green%d\\blue%d;",
                GetRValue(hlpfile->fonts[index].color),
                GetGValue(hlpfile->fonts[index].color),
                GetBValue(hlpfile->fonts[index].color));
        if (!HLPFILE_RtfAddControl(rd, tmp)) return FALSE;
    }
    if (!HLPFILE_RtfAddControl(rd, "}")) return FALSE;

    do
    {
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

        if (index >= hlpfile->topic_maplen) {WINE_WARN("maplen\n"); break;}
        buf = hlpfile->topic_map[index] + offset;
        if (buf + 0x15 >= hlpfile->topic_end) {WINE_WARN("extra\n"); break;}
        end = min(buf + GET_UINT(buf, 0), hlpfile->topic_end);
        if (index != old_index) {offs = 0; old_index = index;}

        switch (buf[0x14])
        {
        case HLP_TOPICHDR:
            if (count++) goto done;
            break;
        case HLP_DISPLAY30:
        case HLP_DISPLAY:
        case HLP_TABLE:
            if (!HLPFILE_BrowseParagraph(page, rd, buf, end, &parlen)) return FALSE;
            if (relative > index * 0x8000 + offs)
                rd->char_pos_rel = rd->char_pos;
            offs += parlen;
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
done:
    page->first_link = rd->first_link;
    return HLPFILE_RtfAddControl(rd, "}");
}