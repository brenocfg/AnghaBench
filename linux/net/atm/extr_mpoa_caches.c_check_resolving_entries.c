#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time64_t ;
struct TYPE_5__ {scalar_t__ mpc_p6; int mpc_p5; int mpc_p4; } ;
struct mpoa_client {int /*<<< orphan*/  ingress_lock; int /*<<< orphan*/  mps_ctrl_addr; TYPE_1__ parameters; TYPE_4__* in_cache; } ;
struct TYPE_7__ {int /*<<< orphan*/  in_dst_ip; } ;
struct TYPE_6__ {TYPE_3__ in_info; } ;
struct k_message {int /*<<< orphan*/  qos; TYPE_2__ content; int /*<<< orphan*/  MPS_ctrl; int /*<<< orphan*/  type; } ;
struct atm_mpoa_qos {int /*<<< orphan*/  qos; } ;
struct TYPE_8__ {scalar_t__ entry_state; scalar_t__ hold_down; scalar_t__ reply_wait; scalar_t__ retry_time; struct TYPE_8__* next; TYPE_3__ ctrl_info; } ;
typedef  TYPE_4__ in_cache_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_ESA_LEN ; 
 scalar_t__ INGRESS_RESOLVING ; 
 int MPC_C1 ; 
 int /*<<< orphan*/  SND_MPOA_RES_RTRY ; 
 struct atm_mpoa_qos* atm_mpoa_search_qos (int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_get_seconds () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_to_mpoad (struct k_message*,struct mpoa_client*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_resolving_entries(struct mpoa_client *client)
{

	struct atm_mpoa_qos *qos;
	in_cache_entry *entry;
	time64_t now;
	struct k_message msg;

	now = ktime_get_seconds();

	read_lock_bh(&client->ingress_lock);
	entry = client->in_cache;
	while (entry != NULL) {
		if (entry->entry_state == INGRESS_RESOLVING) {

			if ((now - entry->hold_down)
					< client->parameters.mpc_p6) {
				entry = entry->next;	/* Entry in hold down */
				continue;
			}
			if ((now - entry->reply_wait) > entry->retry_time) {
				entry->retry_time = MPC_C1 * (entry->retry_time);
				/*
				 * Retry time maximum exceeded,
				 * put entry in hold down.
				 */
				if (entry->retry_time > client->parameters.mpc_p5) {
					entry->hold_down = ktime_get_seconds();
					entry->retry_time = client->parameters.mpc_p4;
					entry = entry->next;
					continue;
				}
				/* Ask daemon to send a resolution request. */
				memset(&entry->hold_down, 0, sizeof(time64_t));
				msg.type = SND_MPOA_RES_RTRY;
				memcpy(msg.MPS_ctrl, client->mps_ctrl_addr, ATM_ESA_LEN);
				msg.content.in_info = entry->ctrl_info;
				qos = atm_mpoa_search_qos(entry->ctrl_info.in_dst_ip);
				if (qos != NULL)
					msg.qos = qos->qos;
				msg_to_mpoad(&msg, client);
				entry->reply_wait = ktime_get_seconds();
			}
		}
		entry = entry->next;
	}
	read_unlock_bh(&client->ingress_lock);
}