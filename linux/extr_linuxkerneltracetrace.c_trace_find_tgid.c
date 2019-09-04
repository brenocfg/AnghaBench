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
 int PID_MAX_DEFAULT ; 
 int* tgid_map ; 
 scalar_t__ unlikely (int) ; 

int trace_find_tgid(int pid)
{
	if (unlikely(!tgid_map || !pid || pid > PID_MAX_DEFAULT))
		return 0;

	return tgid_map[pid];
}