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
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 

__attribute__((used)) static int sequence_finished(__u32 start, int *len, __u32 new)
{
	if (start == INT_MAX)
		return 1;

	if (start == 0 && new == 0) {
		(*len)++;
		return 0;
	}
	if (start != 0 && (start + *len) == new) {
		(*len)++;
		return 0;
	}
	return 1;
}