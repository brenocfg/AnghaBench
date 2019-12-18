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
typedef  int /*<<< orphan*/  u32 ;
struct netlbl_unlhsh_iface {int /*<<< orphan*/  addr4_list; } ;
struct TYPE_2__ {int addr; int mask; int valid; } ;
struct netlbl_unlhsh_addr4 {TYPE_1__ list; int /*<<< orphan*/  secid; } ;
struct in_addr {int s_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (struct netlbl_unlhsh_addr4*) ; 
 struct netlbl_unlhsh_addr4* kzalloc (int,int /*<<< orphan*/ ) ; 
 int netlbl_af4list_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netlbl_unlhsh_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netlbl_unlhsh_add_addr4(struct netlbl_unlhsh_iface *iface,
				   const struct in_addr *addr,
				   const struct in_addr *mask,
				   u32 secid)
{
	int ret_val;
	struct netlbl_unlhsh_addr4 *entry;

	entry = kzalloc(sizeof(*entry), GFP_ATOMIC);
	if (entry == NULL)
		return -ENOMEM;

	entry->list.addr = addr->s_addr & mask->s_addr;
	entry->list.mask = mask->s_addr;
	entry->list.valid = 1;
	entry->secid = secid;

	spin_lock(&netlbl_unlhsh_lock);
	ret_val = netlbl_af4list_add(&entry->list, &iface->addr4_list);
	spin_unlock(&netlbl_unlhsh_lock);

	if (ret_val != 0)
		kfree(entry);
	return ret_val;
}