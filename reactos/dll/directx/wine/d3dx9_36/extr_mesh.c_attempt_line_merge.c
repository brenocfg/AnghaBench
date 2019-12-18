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
struct point2d {scalar_t__ corner; int /*<<< orphan*/  const pos; } ;
struct outline {int count; struct point2d* items; } ;
struct cos_table {int /*<<< orphan*/  cos_half; } ;
typedef  int /*<<< orphan*/  D3DXVECTOR2 ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ POINTTYPE_CORNER ; 
 scalar_t__ POINTTYPE_CURVE_END ; 
 void* POINTTYPE_CURVE_MIDDLE ; 
 void* POINTTYPE_CURVE_START ; 
 scalar_t__ TRUE ; 
 scalar_t__ is_direction_similar (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_vec2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static BOOL attempt_line_merge(struct outline *outline,
                               int pt_index,
                               const D3DXVECTOR2 *nextpt,
                               BOOL to_curve,
                               const struct cos_table *table)
{
    D3DXVECTOR2 curdir, lastdir;
    struct point2d *prevpt, *pt;
    BOOL ret = FALSE;

    pt = &outline->items[pt_index];
    pt_index = (pt_index - 1 + outline->count) % outline->count;
    prevpt = &outline->items[pt_index];

    if (to_curve)
        pt->corner = pt->corner != POINTTYPE_CORNER ? POINTTYPE_CURVE_MIDDLE : POINTTYPE_CURVE_START;

    if (outline->count < 2)
        return FALSE;

    /* remove last point if the next line continues the last line */
    unit_vec2(&lastdir, &prevpt->pos, &pt->pos);
    unit_vec2(&curdir, &pt->pos, nextpt);
    if (is_direction_similar(&lastdir, &curdir, table->cos_half))
    {
        outline->count--;
        if (pt->corner == POINTTYPE_CURVE_END)
            prevpt->corner = pt->corner;
        if (prevpt->corner == POINTTYPE_CURVE_END && to_curve)
            prevpt->corner = POINTTYPE_CURVE_MIDDLE;
        pt = prevpt;

        ret = TRUE;
        if (outline->count < 2)
            return ret;

        pt_index = (pt_index - 1 + outline->count) % outline->count;
        prevpt = &outline->items[pt_index];
        unit_vec2(&lastdir, &prevpt->pos, &pt->pos);
        unit_vec2(&curdir, &pt->pos, nextpt);
    }
    return ret;
}