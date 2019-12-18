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
typedef  scalar_t__ WORD ;
struct TYPE_3__ {scalar_t__ target; int /*<<< orphan*/  ascending; } ;
typedef  size_t INT ;
typedef  TYPE_1__ FindGlyph_struct ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__* bsearch (TYPE_1__*,scalar_t__ const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_FindGlyph ; 

int USP10_FindGlyphInLogClust(const WORD* pwLogClust, int cChars, WORD target)
{
    FindGlyph_struct fgs;
    WORD *ptr;
    INT k;

    if (pwLogClust[0] < pwLogClust[cChars-1])
        fgs.ascending = TRUE;
    else
        fgs.ascending = FALSE;

    fgs.target = target;
    ptr = bsearch(&fgs, pwLogClust, cChars, sizeof(WORD), compare_FindGlyph);

    if (!ptr)
        return -1;

    for (k = (ptr - pwLogClust)-1; k >= 0 && pwLogClust[k] == target; k--)
    ;
    k++;

    return k;
}