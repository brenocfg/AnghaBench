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
struct timer_list {int dummy; } ;
struct hsr_priv {int announce_count; scalar_t__ prot_version; int /*<<< orphan*/  announce_timer; } ;
struct hsr_port {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSR_ANNOUNCE_INTERVAL ; 
 int /*<<< orphan*/  HSR_LIFE_CHECK_INTERVAL ; 
 int /*<<< orphan*/  HSR_PT_MASTER ; 
 int /*<<< orphan*/  HSR_TLV_ANNOUNCE ; 
 int /*<<< orphan*/  HSR_TLV_LIFE_CHECK ; 
 int /*<<< orphan*/  announce_timer ; 
 struct hsr_priv* from_timer (struct hsr_priv*,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct hsr_port* hsr_port_get_hsr (struct hsr_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_admin_up (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  send_hsr_supervision_frame (struct hsr_port*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hsr_announce(struct timer_list *t)
{
	struct hsr_priv *hsr;
	struct hsr_port *master;
	unsigned long interval;

	hsr = from_timer(hsr, t, announce_timer);

	rcu_read_lock();
	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);

	if (hsr->announce_count < 3 && hsr->prot_version == 0) {
		send_hsr_supervision_frame(master, HSR_TLV_ANNOUNCE,
					   hsr->prot_version);
		hsr->announce_count++;

		interval = msecs_to_jiffies(HSR_ANNOUNCE_INTERVAL);
	} else {
		send_hsr_supervision_frame(master, HSR_TLV_LIFE_CHECK,
					   hsr->prot_version);

		interval = msecs_to_jiffies(HSR_LIFE_CHECK_INTERVAL);
	}

	if (is_admin_up(master->dev))
		mod_timer(&hsr->announce_timer, jiffies + interval);

	rcu_read_unlock();
}