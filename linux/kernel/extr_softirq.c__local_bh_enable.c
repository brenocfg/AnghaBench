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
 int /*<<< orphan*/  SOFTIRQ_DISABLE_OFFSET ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __local_bh_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_irq () ; 

void _local_bh_enable(void)
{
	WARN_ON_ONCE(in_irq());
	__local_bh_enable(SOFTIRQ_DISABLE_OFFSET);
}