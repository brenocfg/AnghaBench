#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mpoa_client {int /*<<< orphan*/  ingress_lock; TYPE_2__* in_cache; } ;
struct TYPE_4__ {int in_dst_ip; } ;
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  use; TYPE_1__ ctrl_info; } ;
typedef  TYPE_2__ in_cache_entry ;
typedef  int __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static in_cache_entry *in_cache_get_with_mask(__be32 dst_ip,
					      struct mpoa_client *client,
					      __be32 mask)
{
	in_cache_entry *entry;

	read_lock_bh(&client->ingress_lock);
	entry = client->in_cache;
	while (entry != NULL) {
		if ((entry->ctrl_info.in_dst_ip & mask) == (dst_ip & mask)) {
			refcount_inc(&entry->use);
			read_unlock_bh(&client->ingress_lock);
			return entry;
		}
		entry = entry->next;
	}
	read_unlock_bh(&client->ingress_lock);

	return NULL;

}