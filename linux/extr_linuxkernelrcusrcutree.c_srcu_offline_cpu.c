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
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  srcu_online ; 

void srcu_offline_cpu(unsigned int cpu)
{
	WRITE_ONCE(per_cpu(srcu_online, cpu), false);
}