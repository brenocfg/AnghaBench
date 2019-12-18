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
typedef  int UINT ;
struct TYPE_4__ {int version; int num_phrases; int* phrases_offsets; int* phrases_buffer; int /*<<< orphan*/  hasPhrases; } ;
typedef  TYPE_1__ HLPFILE ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GET_USHORT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HLPFILE_FindSubFile (TYPE_1__*,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  HLPFILE_UncompressLZ77 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int HLPFILE_UncompressedLZ77_Size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINE_WARN (char*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOL HLPFILE_UncompressLZ77_Phrases(HLPFILE* hlpfile)
{
    UINT i, num, dec_size, head_size;
    BYTE *buf, *end;

    if (!HLPFILE_FindSubFile(hlpfile, "|Phrases", &buf, &end)) return FALSE;

    if (hlpfile->version <= 16)
        head_size = 13;
    else
        head_size = 17;

    num = hlpfile->num_phrases = GET_USHORT(buf, 9);
    if (buf + 2 * num + 0x13 >= end) {WINE_WARN("1a\n"); return FALSE;};

    if (hlpfile->version <= 16)
        dec_size = end - buf - 15 - 2 * num;
    else
        dec_size = HLPFILE_UncompressedLZ77_Size(buf + 0x13 + 2 * num, end);

    hlpfile->phrases_offsets = HeapAlloc(GetProcessHeap(), 0, sizeof(unsigned) * (num + 1));
    hlpfile->phrases_buffer  = HeapAlloc(GetProcessHeap(), 0, dec_size);
    if (!hlpfile->phrases_offsets || !hlpfile->phrases_buffer)
    {
        HeapFree(GetProcessHeap(), 0, hlpfile->phrases_offsets);
        HeapFree(GetProcessHeap(), 0, hlpfile->phrases_buffer);
        return FALSE;
    }

    for (i = 0; i <= num; i++)
        hlpfile->phrases_offsets[i] = GET_USHORT(buf, head_size + 2 * i) - 2 * num - 2;

    if (hlpfile->version <= 16)
        memcpy(hlpfile->phrases_buffer, buf + 15 + 2*num, dec_size);
    else
        HLPFILE_UncompressLZ77(buf + 0x13 + 2 * num, end, (BYTE*)hlpfile->phrases_buffer);

    hlpfile->hasPhrases = TRUE;
    return TRUE;
}