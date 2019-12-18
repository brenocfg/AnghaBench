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
typedef  int /*<<< orphan*/  GLenum ;
typedef  unsigned int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 unsigned int* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ptx_compress_dxtn (int,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline BOOL x8r8g8b8_to_dxtn(const BYTE *src, BYTE *dst, DWORD pitch_in,
        DWORD pitch_out, unsigned int w, unsigned int h, GLenum destformat, BOOL alpha)
{
    unsigned int x, y;
    DWORD color, *tmp;

    TRACE("Converting %ux%u pixels, pitches %u %u\n", w, h, pitch_in, pitch_out);

    tmp = HeapAlloc(GetProcessHeap(), 0, h * w * sizeof(DWORD));
    if (!tmp)
    {
        ERR("Failed to allocate memory for conversion\n");
        return FALSE;
    }

    for (y = 0; y < h; ++y)
    {
        const DWORD *src_line = (const DWORD *)(src + y * pitch_in);
        DWORD *dst_line = tmp + y * w;
        for (x = 0; x < w; ++x)
        {
            color = src_line[x];
            if (alpha)
            {
                dst_line[x] = (color & 0xff00ff00) | ((color & 0xff) << 16) |
                              ((color & 0xff0000) >> 16);
            }
            else
            {
                dst_line[x] = 0xff000000 | ((color & 0xff) << 16) |
                              (color & 0xff00) | ((color & 0xff0000) >> 16);
            }
        }
    }

    ptx_compress_dxtn(4, w, h, (BYTE *)tmp, destformat, dst, pitch_out);
    HeapFree(GetProcessHeap(), 0, tmp);
    return TRUE;
}