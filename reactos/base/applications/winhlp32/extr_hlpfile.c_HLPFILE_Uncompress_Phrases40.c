#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
typedef  int UINT ;
struct TYPE_4__ {int num_phrases; int /*<<< orphan*/  hasPhrases40; scalar_t__* phrases_buffer; scalar_t__* phrases_offsets; } ;
typedef  int INT ;
typedef  TYPE_1__ HLPFILE ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GET_UINT (int /*<<< orphan*/ *,int) ; 
 int GET_USHORT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HLPFILE_FindSubFile (TYPE_1__*,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  HLPFILE_UncompressLZ77 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int HLPFILE_UncompressedLZ77_Size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINE_TRACE (char*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  WINE_WARN (char*,int,int) ; 
 scalar_t__ getbit () ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOL HLPFILE_Uncompress_Phrases40(HLPFILE* hlpfile)
{
    UINT num;
    INT dec_size, cpr_size;
    BYTE *buf_idx, *end_idx;
    BYTE *buf_phs, *end_phs;
    ULONG* ptr, mask = 0;
    unsigned int i;
    unsigned short bc, n;

    if (!HLPFILE_FindSubFile(hlpfile, "|PhrIndex", &buf_idx, &end_idx) ||
        !HLPFILE_FindSubFile(hlpfile, "|PhrImage", &buf_phs, &end_phs)) return FALSE;

    ptr = (ULONG*)(buf_idx + 9 + 28);
    bc = GET_USHORT(buf_idx, 9 + 24) & 0x0F;
    num = hlpfile->num_phrases = GET_USHORT(buf_idx, 9 + 4);

    WINE_TRACE("Index: Magic=%08x #entries=%u CpsdSize=%u PhrImgSize=%u\n"
               "\tPhrImgCprsdSize=%u 0=%u bc=%x ukn=%x\n",
               GET_UINT(buf_idx, 9 + 0),
               GET_UINT(buf_idx, 9 + 4),
               GET_UINT(buf_idx, 9 + 8),
               GET_UINT(buf_idx, 9 + 12),
               GET_UINT(buf_idx, 9 + 16),
               GET_UINT(buf_idx, 9 + 20),
               GET_USHORT(buf_idx, 9 + 24),
               GET_USHORT(buf_idx, 9 + 26));

    dec_size = GET_UINT(buf_idx, 9 + 12);
    cpr_size = GET_UINT(buf_idx, 9 + 16);

    if (dec_size != cpr_size &&
        dec_size != HLPFILE_UncompressedLZ77_Size(buf_phs + 9, end_phs))
    {
        WINE_WARN("size mismatch %u %u\n",
                  dec_size, HLPFILE_UncompressedLZ77_Size(buf_phs + 9, end_phs));
        dec_size = max(dec_size, HLPFILE_UncompressedLZ77_Size(buf_phs + 9, end_phs));
    }

    hlpfile->phrases_offsets = HeapAlloc(GetProcessHeap(), 0, sizeof(unsigned) * (num + 1));
    hlpfile->phrases_buffer  = HeapAlloc(GetProcessHeap(), 0, dec_size);
    if (!hlpfile->phrases_offsets || !hlpfile->phrases_buffer)
    {
        HeapFree(GetProcessHeap(), 0, hlpfile->phrases_offsets);
        HeapFree(GetProcessHeap(), 0, hlpfile->phrases_buffer);
        return FALSE;
    }

#define getbit() ((mask <<= 1) ? (*ptr & mask) != 0: (*++ptr & (mask=1)) != 0)

    hlpfile->phrases_offsets[0] = 0;
    ptr--; /* as we'll first increment ptr because mask is 0 on first getbit() call */
    for (i = 0; i < num; i++)
    {
        for (n = 1; getbit(); n += 1 << bc);
        if (getbit()) n++;
        if (bc > 1 && getbit()) n += 2;
        if (bc > 2 && getbit()) n += 4;
        if (bc > 3 && getbit()) n += 8;
        if (bc > 4 && getbit()) n += 16;
        hlpfile->phrases_offsets[i + 1] = hlpfile->phrases_offsets[i] + n;
    }
#undef getbit

    if (dec_size == cpr_size)
        memcpy(hlpfile->phrases_buffer, buf_phs + 9, dec_size);
    else
        HLPFILE_UncompressLZ77(buf_phs + 9, end_phs, (BYTE*)hlpfile->phrases_buffer);

    hlpfile->hasPhrases40 = TRUE;
    return TRUE;
}