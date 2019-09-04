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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int cache_clean () ; 
 int /*<<< orphan*/  cache_cleaner ; 
 int /*<<< orphan*/  cache_list ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int round_jiffies_relative (int) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static void do_cache_clean(struct work_struct *work)
{
	int delay = 5;
	if (cache_clean() == -1)
		delay = round_jiffies_relative(30*HZ);

	if (list_empty(&cache_list))
		delay = 0;

	if (delay)
		queue_delayed_work(system_power_efficient_wq,
				   &cache_cleaner, delay);
}