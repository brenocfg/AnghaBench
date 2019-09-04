#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct RtfData {int dummy; } ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  HLPFILE ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int GET_UINT (int /*<<< orphan*/  const*,int) ; 
 int GET_USHORT (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HLPFILE_AddHotSpotLinks (struct RtfData*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/ * HLPFILE_DecompressGfx (int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ HLPFILE_RtfAddControl (struct RtfData*,char*) ; 
 scalar_t__ HLPFILE_RtfAddHexBytes (struct RtfData*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WINE_TRACE (char*,...) ; 
 int fetch_ulong (int /*<<< orphan*/  const**) ; 
 unsigned int fetch_ushort (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int,int,int) ; 

__attribute__((used)) static BOOL     HLPFILE_RtfAddMetaFile(struct RtfData* rd, HLPFILE* file, const BYTE* beg, BYTE pack)
{
    ULONG               size, csize, off, hs_offset, hs_size;
    const BYTE*         ptr;
    const BYTE*         bits;
    BYTE*               alloc = NULL;
    char                tmp[256];
    unsigned            mm;
    BOOL                ret;

    WINE_TRACE("Loading metafile\n");

    ptr = beg + 2; /* for type and pack */

    mm = fetch_ushort(&ptr); /* mapping mode */
    sprintf(tmp, "{\\pict\\wmetafile%u\\picw%u\\pich%u",
            mm, GET_USHORT(ptr, 0), GET_USHORT(ptr, 2));
    if (!HLPFILE_RtfAddControl(rd, tmp)) return FALSE;
    ptr += 4;

    size = fetch_ulong(&ptr); /* decompressed size */
    csize = fetch_ulong(&ptr); /* compressed size */
    hs_size = fetch_ulong(&ptr); /* hotspot size */
    off = GET_UINT(ptr, 0);
    hs_offset = GET_UINT(ptr, 4);
    ptr += 8;

    HLPFILE_AddHotSpotLinks(rd, file, beg, hs_size, hs_offset);

    WINE_TRACE("sz=%u csz=%u offs=%u/%u,%u/%u\n",
               size, csize, off, (ULONG)(ptr - beg), hs_size, hs_offset);

    bits = HLPFILE_DecompressGfx(beg + off, csize, size, pack, &alloc);
    if (!bits) return FALSE;

    ret = HLPFILE_RtfAddHexBytes(rd, bits, size) &&
        HLPFILE_RtfAddControl(rd, "}");

    HeapFree(GetProcessHeap(), 0, alloc);

    return ret;
}