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
 int raw_smp_processor_id () ; 

__attribute__((used)) static inline int shadow_pid(int realpid)
{
	if (realpid)
		return realpid;

	return -raw_smp_processor_id() - 2;
}