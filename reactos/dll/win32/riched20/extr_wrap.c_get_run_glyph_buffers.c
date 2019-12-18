#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_3__ {int max_glyphs; int* advances; scalar_t__ glyphs; int /*<<< orphan*/ * offsets; int /*<<< orphan*/ * vis_attrs; } ;
typedef  int /*<<< orphan*/  SCRIPT_VISATTR ;
typedef  TYPE_1__ ME_Run ;
typedef  int /*<<< orphan*/  GOFFSET ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (scalar_t__) ; 

__attribute__((used)) static BOOL get_run_glyph_buffers( ME_Run *run )
{
    heap_free( run->glyphs );
    run->glyphs = heap_alloc( run->max_glyphs * (sizeof(WORD) + sizeof(SCRIPT_VISATTR) + sizeof(int) + sizeof(GOFFSET)) );
    if (!run->glyphs) return FALSE;

    run->vis_attrs = (SCRIPT_VISATTR*)((char*)run->glyphs + run->max_glyphs * sizeof(WORD));
    run->advances = (int*)((char*)run->glyphs + run->max_glyphs * (sizeof(WORD) + sizeof(SCRIPT_VISATTR)));
    run->offsets = (GOFFSET*)((char*)run->glyphs + run->max_glyphs * (sizeof(WORD) + sizeof(SCRIPT_VISATTR) + sizeof(int)));

    return TRUE;
}