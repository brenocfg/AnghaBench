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
typedef  int u32 ;
struct fsl_soc_die_attr {int svr; int mask; } ;

/* Variables and functions */

__attribute__((used)) static const struct fsl_soc_die_attr *fsl_soc_die_match(
	u32 svr, const struct fsl_soc_die_attr *matches)
{
	while (matches->svr) {
		if (matches->svr == (svr & matches->mask))
			return matches;
		matches++;
	};
	return NULL;
}