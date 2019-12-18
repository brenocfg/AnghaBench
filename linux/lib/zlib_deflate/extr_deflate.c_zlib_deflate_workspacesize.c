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
typedef  int /*<<< orphan*/  deflate_workspace ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MAX_MEM_LEVEL ; 
 int zlib_deflate_head_memsize (int) ; 
 int zlib_deflate_overlay_memsize (int) ; 
 int zlib_deflate_prev_memsize (int) ; 
 int zlib_deflate_window_memsize (int) ; 

int zlib_deflate_workspacesize(int windowBits, int memLevel)
{
    if (windowBits < 0) /* undocumented feature: suppress zlib header */
        windowBits = -windowBits;

    /* Since the return value is typically passed to vmalloc() unchecked... */
    BUG_ON(memLevel < 1 || memLevel > MAX_MEM_LEVEL || windowBits < 9 ||
							windowBits > 15);

    return sizeof(deflate_workspace)
        + zlib_deflate_window_memsize(windowBits)
        + zlib_deflate_prev_memsize(windowBits)
        + zlib_deflate_head_memsize(memLevel)
        + zlib_deflate_overlay_memsize(memLevel);
}