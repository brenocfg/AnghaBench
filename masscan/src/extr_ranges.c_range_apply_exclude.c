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
struct Range {int begin; int end; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
range_apply_exclude(const struct Range exclude, struct Range *target, struct Range *split)
{
    /* Set 'split' to invalid to start with */
    split->begin = 2;
    split->end = 1;

    /* Case 1: no overlap */
    if (target->begin > exclude.end || target->end < exclude.begin) {
        return;
    }
    
    /* Case 2: complete overlap, mark target as invalid and return */
    if (target->begin >= exclude.begin && target->end <= exclude.end) {
        target->begin = 2;
        target->end = 1;
        return;
    }
    
    /* Case 3: overlap at start */
    if (target->begin >= exclude.begin && target->end > exclude.end) {
        target->begin = exclude.end + 1;
        return;
    }
    
    /* Case 4: overlap at end */
    if (target->begin < exclude.begin && target->end <= exclude.end) {
        target->end = exclude.begin - 1;
        return;
    }
    
    /* Case 5: this range needs to be split */
    if (target->begin < exclude.begin && target->end > exclude.end) {
        split->end = target->end;
        split->begin = exclude.end + 1;
        target->end = exclude.begin - 1;
        return;
    }
    
    /* No other condition should be possible */
    assert(!"possible");
}