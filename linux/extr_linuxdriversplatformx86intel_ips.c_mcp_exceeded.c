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
typedef  scalar_t__ u32 ;
struct ips_driver {int mcp_temp_limit; scalar_t__ mcp_avg_temp; scalar_t__ cpu_avg_power; scalar_t__ mch_avg_power; scalar_t__ mcp_power_limit; int /*<<< orphan*/  turbo_status_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool mcp_exceeded(struct ips_driver *ips)
{
	unsigned long flags;
	bool ret = false;
	u32 temp_limit;
	u32 avg_power;

	spin_lock_irqsave(&ips->turbo_status_lock, flags);

	temp_limit = ips->mcp_temp_limit * 100;
	if (ips->mcp_avg_temp > temp_limit)
		ret = true;

	avg_power = ips->cpu_avg_power + ips->mch_avg_power;
	if (avg_power > ips->mcp_power_limit)
		ret = true;

	spin_unlock_irqrestore(&ips->turbo_status_lock, flags);

	return ret;
}