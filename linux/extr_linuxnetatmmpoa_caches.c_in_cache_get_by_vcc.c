#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mpoa_client {int /*<<< orphan*/  ingress_lock; TYPE_1__* in_cache; } ;
struct atm_vcc {int dummy; } ;
struct TYPE_3__ {struct TYPE_3__* next; int /*<<< orphan*/  use; struct atm_vcc* shortcut; } ;
typedef  TYPE_1__ in_cache_entry ;

/* Variables and functions */
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static in_cache_entry *in_cache_get_by_vcc(struct atm_vcc *vcc,
					   struct mpoa_client *client)
{
	in_cache_entry *entry;

	read_lock_bh(&client->ingress_lock);
	entry = client->in_cache;
	while (entry != NULL) {
		if (entry->shortcut == vcc) {
			refcount_inc(&entry->use);
			read_unlock_bh(&client->ingress_lock);
			return entry;
		}
		entry = entry->next;
	}
	read_unlock_bh(&client->ingress_lock);

	return NULL;
}