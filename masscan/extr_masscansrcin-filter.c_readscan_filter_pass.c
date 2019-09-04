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
struct RangeList {scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  rangelist_is_contains (struct RangeList const*,unsigned int) ; 

int
readscan_filter_pass(unsigned ip, unsigned port, unsigned type,
              const struct RangeList *ips,
              const struct RangeList *ports,
              const struct RangeList *btypes)
{
    if (ips && ips->count) {
        if (!rangelist_is_contains(ips, ip))
            return 0;
    }
    if (ports && ports->count) {
        if (!rangelist_is_contains(ports, port))
            return 0;
    }
    if (btypes && btypes->count) {
        if (!rangelist_is_contains(btypes, type))
            return 0;
    }

    return 1;
}