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
struct xt_counters {int dummy; } ;

/* Variables and functions */
 int INT_MAX ; 
 unsigned int XT_MAX_TABLE_SIZE ; 
 struct xt_counters* vzalloc (unsigned int) ; 

struct xt_counters *xt_counters_alloc(unsigned int counters)
{
	struct xt_counters *mem;

	if (counters == 0 || counters > INT_MAX / sizeof(*mem))
		return NULL;

	counters *= sizeof(*mem);
	if (counters > XT_MAX_TABLE_SIZE)
		return NULL;

	return vzalloc(counters);
}