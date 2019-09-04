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
struct Range6List {unsigned int count; struct Range6* list; } ;
struct Range6 {int /*<<< orphan*/  const end; int /*<<< orphan*/  const begin; } ;
typedef  int /*<<< orphan*/  ipv6address ;

/* Variables and functions */
 scalar_t__ LESSEQ (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

int
range6list_is_contains(const struct Range6List *targets, const ipv6address ip)
{
    unsigned i;

    for (i=0; i<targets->count; i++) {
        struct Range6 *range = &targets->list[i];

        if (LESSEQ(range->begin, ip) && LESSEQ(ip, range->end))
            return 1;
    }
    return 0;
}