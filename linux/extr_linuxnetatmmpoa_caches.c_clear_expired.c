#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time64_t ;
struct mpoa_client {int /*<<< orphan*/  egress_lock; TYPE_3__* eg_ops; TYPE_4__* eg_cache; } ;
struct TYPE_7__ {scalar_t__ holding_time; int /*<<< orphan*/  cache_id; } ;
struct TYPE_6__ {TYPE_2__ eg_info; } ;
struct k_message {TYPE_1__ content; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {scalar_t__ time; TYPE_2__ ctrl_info; struct TYPE_9__* next; } ;
typedef  TYPE_4__ eg_cache_entry ;
struct TYPE_8__ {int /*<<< orphan*/  (* remove_entry ) (TYPE_4__*,struct mpoa_client*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SND_EGRESS_PURGE ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_get_seconds () ; 
 int /*<<< orphan*/  msg_to_mpoad (struct k_message*,struct mpoa_client*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,struct mpoa_client*) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_expired(struct mpoa_client *client)
{
	eg_cache_entry *entry, *next_entry;
	time64_t now;
	struct k_message msg;

	now = ktime_get_seconds();

	write_lock_irq(&client->egress_lock);
	entry = client->eg_cache;
	while (entry != NULL) {
		next_entry = entry->next;
		if ((now - entry->time) > entry->ctrl_info.holding_time) {
			msg.type = SND_EGRESS_PURGE;
			msg.content.eg_info = entry->ctrl_info;
			dprintk("egress_cache: holding time expired, cache_id = %u.\n",
				ntohl(entry->ctrl_info.cache_id));
			msg_to_mpoad(&msg, client);
			client->eg_ops->remove_entry(entry, client);
		}
		entry = next_entry;
	}
	write_unlock_irq(&client->egress_lock);
}