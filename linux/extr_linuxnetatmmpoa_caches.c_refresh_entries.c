#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int time64_t ;
struct mpoa_client {int /*<<< orphan*/  ingress_lock; struct in_cache_entry* in_cache; } ;
struct TYPE_2__ {int holding_time; } ;
struct in_cache_entry {scalar_t__ entry_state; int refresh_time; int reply_wait; struct in_cache_entry* next; TYPE_1__ ctrl_info; } ;

/* Variables and functions */
 scalar_t__ INGRESS_REFRESHING ; 
 scalar_t__ INGRESS_RESOLVED ; 
 int /*<<< orphan*/  ddprintk (char*) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int ktime_get_seconds () ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void refresh_entries(struct mpoa_client *client)
{
	time64_t now;
	struct in_cache_entry *entry = client->in_cache;

	ddprintk("refresh_entries\n");
	now = ktime_get_seconds();

	read_lock_bh(&client->ingress_lock);
	while (entry != NULL) {
		if (entry->entry_state == INGRESS_RESOLVED) {
			if (!(entry->refresh_time))
				entry->refresh_time = (2 * (entry->ctrl_info.holding_time))/3;
			if ((now - entry->reply_wait) >
			    entry->refresh_time) {
				dprintk("refreshing an entry.\n");
				entry->entry_state = INGRESS_REFRESHING;

			}
		}
		entry = entry->next;
	}
	read_unlock_bh(&client->ingress_lock);
}