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
struct ef4_filter_spec {int* loc_mac; int /*<<< orphan*/  match_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_FILTER_MATCH_LOC_MAC_IG ; 

__attribute__((used)) static inline int ef4_filter_set_mc_def(struct ef4_filter_spec *spec)
{
	spec->match_flags |= EF4_FILTER_MATCH_LOC_MAC_IG;
	spec->loc_mac[0] = 1;
	return 0;
}