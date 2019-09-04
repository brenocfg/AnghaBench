#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mpoa_client {int /*<<< orphan*/  egress_lock; int /*<<< orphan*/  mps_ctrl_addr; TYPE_3__* eg_cache; } ;
struct TYPE_7__ {int /*<<< orphan*/  mps_ip; int /*<<< orphan*/  cache_id; int /*<<< orphan*/  eg_dst_ip; } ;
struct TYPE_6__ {TYPE_2__ eg_info; } ;
struct k_message {TYPE_1__ content; } ;
struct TYPE_8__ {int /*<<< orphan*/  use; TYPE_2__ ctrl_info; int /*<<< orphan*/  entry_state; int /*<<< orphan*/  time; int /*<<< orphan*/  MPS_ctrl_ATM_addr; struct TYPE_8__* prev; struct TYPE_8__* next; } ;
typedef  TYPE_3__ eg_cache_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_ESA_LEN ; 
 int /*<<< orphan*/  EGRESS_RESOLVED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  ktime_get_seconds () ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static eg_cache_entry *eg_cache_add_entry(struct k_message *msg,
					  struct mpoa_client *client)
{
	eg_cache_entry *entry = kzalloc(sizeof(eg_cache_entry), GFP_KERNEL);

	if (entry == NULL) {
		pr_info("out of memory\n");
		return NULL;
	}

	dprintk("adding an egress entry, ip = %pI4, this should be our IP\n",
		&msg->content.eg_info.eg_dst_ip);

	refcount_set(&entry->use, 1);
	dprintk("new_eg_cache_entry: about to lock\n");
	write_lock_irq(&client->egress_lock);
	entry->next = client->eg_cache;
	entry->prev = NULL;
	if (client->eg_cache != NULL)
		client->eg_cache->prev = entry;
	client->eg_cache = entry;

	memcpy(entry->MPS_ctrl_ATM_addr, client->mps_ctrl_addr, ATM_ESA_LEN);
	entry->ctrl_info = msg->content.eg_info;
	entry->time = ktime_get_seconds();
	entry->entry_state = EGRESS_RESOLVED;
	dprintk("new_eg_cache_entry cache_id %u\n",
		ntohl(entry->ctrl_info.cache_id));
	dprintk("mps_ip = %pI4\n", &entry->ctrl_info.mps_ip);
	refcount_inc(&entry->use);

	write_unlock_irq(&client->egress_lock);
	dprintk("new_eg_cache_entry: unlocked\n");

	return entry;
}