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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 scalar_t__ COUNT_MASK ; 
 scalar_t__ count_threshold ; 

__attribute__((used)) static int count_threshold_set(void *data, u64 val)
{
	*(u64 *)data = val;

	if (val > COUNT_MASK)
		val = COUNT_MASK;

	count_threshold = val;

	return 0;
}