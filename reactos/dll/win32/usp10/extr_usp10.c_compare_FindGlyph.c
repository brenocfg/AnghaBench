#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_2__ {scalar_t__ const target; int /*<<< orphan*/  ascending; } ;
typedef  TYPE_1__ FindGlyph_struct ;

/* Variables and functions */

__attribute__((used)) static int compare_FindGlyph(const void *a, const void* b)
{
    const FindGlyph_struct *find = (FindGlyph_struct*)a;
    const WORD *idx= (WORD*)b;
    int rc = 0;

    if ( find->target > *idx)
        rc = 1;
    else if (find->target < *idx)
        rc = -1;

    if (!find->ascending)
        rc *= -1;
    return rc;
}