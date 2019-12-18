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
typedef  int BYTE ;

/* Variables and functions */
 int const* FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HLPFILE_UncompressLZ77 (int const*,int const*,int*) ; 
 int /*<<< orphan*/  HLPFILE_UncompressRLE (int const*,int const*,int*,unsigned int) ; 
 unsigned int HLPFILE_UncompressedLZ77_Size (int const*,int const*) ; 
 int* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  WINE_FIXME (char*,int) ; 
 int /*<<< orphan*/  WINE_TRACE (char*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  WINE_WARN (char*,unsigned int,unsigned int) ; 

__attribute__((used)) static const BYTE*      HLPFILE_DecompressGfx(const BYTE* src, unsigned csz, unsigned sz, BYTE packing,
                                              BYTE** alloc)
{
    const BYTE* dst;
    BYTE*       tmp;
    unsigned    sz77;

    WINE_TRACE("Unpacking (%d) from %u bytes to %u bytes\n", packing, csz, sz);

    switch (packing)
    {
    case 0: /* uncompressed */
        if (sz != csz)
            WINE_WARN("Bogus gfx sizes (uncompressed): %u / %u\n", sz, csz);
        dst = src;
        *alloc = NULL;
        break;
    case 1: /* RunLen */
        dst = *alloc = HeapAlloc(GetProcessHeap(), 0, sz);
        if (!dst) return NULL;
        HLPFILE_UncompressRLE(src, src + csz, *alloc, sz);
        break;
    case 2: /* LZ77 */
        sz77 = HLPFILE_UncompressedLZ77_Size(src, src + csz);
        dst = *alloc = HeapAlloc(GetProcessHeap(), 0, sz77);
        if (!dst) return NULL;
        HLPFILE_UncompressLZ77(src, src + csz, *alloc);
        if (sz77 != sz)
            WINE_WARN("Bogus gfx sizes (LZ77): %u / %u\n", sz77, sz);
        break;
    case 3: /* LZ77 then RLE */
        sz77 = HLPFILE_UncompressedLZ77_Size(src, src + csz);
        tmp = HeapAlloc(GetProcessHeap(), 0, sz77);
        if (!tmp) return FALSE;
        HLPFILE_UncompressLZ77(src, src + csz, tmp);
        dst = *alloc = HeapAlloc(GetProcessHeap(), 0, sz);
        if (!dst)
        {
            HeapFree(GetProcessHeap(), 0, tmp);
            return FALSE;
        }
        HLPFILE_UncompressRLE(tmp, tmp + sz77, *alloc, sz);
        HeapFree(GetProcessHeap(), 0, tmp);
        break;
    default:
        WINE_FIXME("Unsupported packing %u\n", packing);
        return NULL;
    }
    return dst;
}