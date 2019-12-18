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
struct per_cpu_dm_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  hw_entries; int /*<<< orphan*/  send_timer; } ;
struct net_dm_hw_entries {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  dm_hit_limit ; 
 int /*<<< orphan*/  entries ; 
 scalar_t__ jiffies ; 
 struct net_dm_hw_entries* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  struct_size (struct net_dm_hw_entries*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,struct net_dm_hw_entries*) ; 

__attribute__((used)) static struct net_dm_hw_entries *
net_dm_hw_reset_per_cpu_data(struct per_cpu_dm_data *hw_data)
{
	struct net_dm_hw_entries *hw_entries;
	unsigned long flags;

	hw_entries = kzalloc(struct_size(hw_entries, entries, dm_hit_limit),
			     GFP_KERNEL);
	if (!hw_entries) {
		/* If the memory allocation failed, we try to perform another
		 * allocation in 1/10 second. Otherwise, the probe function
		 * will constantly bail out.
		 */
		mod_timer(&hw_data->send_timer, jiffies + HZ / 10);
	}

	spin_lock_irqsave(&hw_data->lock, flags);
	swap(hw_data->hw_entries, hw_entries);
	spin_unlock_irqrestore(&hw_data->lock, flags);

	return hw_entries;
}