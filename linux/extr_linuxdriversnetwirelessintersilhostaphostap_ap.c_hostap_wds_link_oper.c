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
typedef  int /*<<< orphan*/  wds_oper_type ;
typedef  int /*<<< orphan*/  u8 ;
struct wds_oper_data {struct wds_oper_data* next; int /*<<< orphan*/  type; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {TYPE_1__* ap; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ local_info_t ;
struct TYPE_4__ {int /*<<< orphan*/  wds_oper_queue; struct wds_oper_data* wds_oper_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct wds_oper_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void hostap_wds_link_oper(local_info_t *local, u8 *addr, wds_oper_type type)
{
	struct wds_oper_data *entry;

	entry = kmalloc(sizeof(*entry), GFP_ATOMIC);
	if (!entry)
		return;
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->type = type;
	spin_lock_bh(&local->lock);
	entry->next = local->ap->wds_oper_entries;
	local->ap->wds_oper_entries = entry;
	spin_unlock_bh(&local->lock);

	schedule_work(&local->ap->wds_oper_queue);
}