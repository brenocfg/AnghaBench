#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct Range6List {unsigned int count; TYPE_1__* list; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ const ipv6address ;
struct TYPE_5__ {int /*<<< orphan*/  begin; int /*<<< orphan*/  end; } ;

/* Variables and functions */
 TYPE_2__ const ADD1 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ DIFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static ipv6address
range6list_pick_linearsearch(const struct Range6List *targets, uint64_t index)
{
    static const ipv6address emptyaddress = {0,0};
    unsigned i;

    for (i=0; i<targets->count; i++) {
        uint64_t range = DIFF(targets->list[i].end, targets->list[i].begin) + 1ULL;
        if (index < range)
            return ADD1(targets->list[i].begin, index);
        else
            index -= range;
    }

    assert(!"end of list");
    return emptyaddress;
}