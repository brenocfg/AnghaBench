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

/* Variables and functions */
 int EINVAL ; 
 unsigned long TRACING_MAP_BITS_MAX ; 
 unsigned long TRACING_MAP_BITS_MIN ; 
 unsigned long ilog2 (int /*<<< orphan*/ ) ; 
 int kstrtoul (char*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  roundup_pow_of_two (unsigned long) ; 
 int /*<<< orphan*/  strsep (char**,char*) ; 

__attribute__((used)) static int parse_map_size(char *str)
{
	unsigned long size, map_bits;
	int ret;

	strsep(&str, "=");
	if (!str) {
		ret = -EINVAL;
		goto out;
	}

	ret = kstrtoul(str, 0, &size);
	if (ret)
		goto out;

	map_bits = ilog2(roundup_pow_of_two(size));
	if (map_bits < TRACING_MAP_BITS_MIN ||
	    map_bits > TRACING_MAP_BITS_MAX)
		ret = -EINVAL;
	else
		ret = map_bits;
 out:
	return ret;
}