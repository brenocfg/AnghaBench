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
struct net_device {unsigned char operstate; } ;
struct hsr_priv {int /*<<< orphan*/  announce_timer; scalar_t__ announce_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSR_ANNOUNCE_INTERVAL ; 
 unsigned char IF_OPER_UP ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct hsr_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void hsr_check_announce(struct net_device *hsr_dev,
			       unsigned char old_operstate)
{
	struct hsr_priv *hsr;

	hsr = netdev_priv(hsr_dev);

	if (hsr_dev->operstate == IF_OPER_UP && old_operstate != IF_OPER_UP) {
		/* Went up */
		hsr->announce_count = 0;
		mod_timer(&hsr->announce_timer,
			  jiffies + msecs_to_jiffies(HSR_ANNOUNCE_INTERVAL));
	}

	if (hsr_dev->operstate != IF_OPER_UP && old_operstate == IF_OPER_UP)
		/* Went down */
		del_timer(&hsr->announce_timer);
}