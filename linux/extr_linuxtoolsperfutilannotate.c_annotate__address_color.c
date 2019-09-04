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
struct block_range {int dummy; } ;

/* Variables and functions */
 char const* PERF_COLOR_MAGENTA ; 
 char const* PERF_COLOR_NORMAL ; 
 char const* PERF_COLOR_RED ; 
 double block_range__coverage (struct block_range*) ; 

__attribute__((used)) static const char *annotate__address_color(struct block_range *br)
{
	double cov = block_range__coverage(br);

	if (cov >= 0) {
		/* mark red for >75% coverage */
		if (cov > 0.75)
			return PERF_COLOR_RED;

		/* mark dull for <1% coverage */
		if (cov < 0.01)
			return PERF_COLOR_NORMAL;
	}

	return PERF_COLOR_MAGENTA;
}