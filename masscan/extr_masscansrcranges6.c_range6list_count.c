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
typedef  scalar_t__ uint64_t ;
struct Range6List {unsigned int count; TYPE_1__* list; } ;
struct TYPE_2__ {int /*<<< orphan*/  begin; int /*<<< orphan*/  end; } ;

/* Variables and functions */
 scalar_t__ DIFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

uint64_t
range6list_count(const struct Range6List *targets)
{
    unsigned i;
    uint64_t result = 0;

    for (i=0; i<targets->count; i++) {
        uint64_t result_old = result;

        result += DIFF(targets->list[i].end, targets->list[i].begin) + 1ULL;
        if (result < result_old) {
            /* integer overflow */
            fprintf(stderr, "targe range bigger than 64-bits\n");
            return ~0ULL;
        }
    }

    return result;
}