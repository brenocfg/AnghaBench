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
struct switchdev_trans {int dummy; } ;
struct dsa_port {unsigned int ageing_time; } ;
struct dsa_notifier_ageing_time_info {unsigned int ageing_time; struct switchdev_trans* trans; } ;
typedef  int /*<<< orphan*/  clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_NOTIFIER_AGEING_TIME ; 
 unsigned long clock_t_to_jiffies (int /*<<< orphan*/ ) ; 
 int dsa_port_notify (struct dsa_port*,int /*<<< orphan*/ ,struct dsa_notifier_ageing_time_info*) ; 
 unsigned int jiffies_to_msecs (unsigned long) ; 
 scalar_t__ switchdev_trans_ph_prepare (struct switchdev_trans*) ; 

int dsa_port_ageing_time(struct dsa_port *dp, clock_t ageing_clock,
			 struct switchdev_trans *trans)
{
	unsigned long ageing_jiffies = clock_t_to_jiffies(ageing_clock);
	unsigned int ageing_time = jiffies_to_msecs(ageing_jiffies);
	struct dsa_notifier_ageing_time_info info = {
		.ageing_time = ageing_time,
		.trans = trans,
	};

	if (switchdev_trans_ph_prepare(trans))
		return dsa_port_notify(dp, DSA_NOTIFIER_AGEING_TIME, &info);

	dp->ageing_time = ageing_time;

	return dsa_port_notify(dp, DSA_NOTIFIER_AGEING_TIME, &info);
}