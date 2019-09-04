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
struct netdev_hw_addr_list {int /*<<< orphan*/  count; int /*<<< orphan*/  list; } ;
struct netdev_hw_addr {unsigned char type; int refcount; int global_use; int synced; int /*<<< orphan*/  list; scalar_t__ sync_cnt; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int L1_CACHE_BYTES ; 
 struct netdev_hw_addr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 

__attribute__((used)) static int __hw_addr_create_ex(struct netdev_hw_addr_list *list,
			       const unsigned char *addr, int addr_len,
			       unsigned char addr_type, bool global,
			       bool sync)
{
	struct netdev_hw_addr *ha;
	int alloc_size;

	alloc_size = sizeof(*ha);
	if (alloc_size < L1_CACHE_BYTES)
		alloc_size = L1_CACHE_BYTES;
	ha = kmalloc(alloc_size, GFP_ATOMIC);
	if (!ha)
		return -ENOMEM;
	memcpy(ha->addr, addr, addr_len);
	ha->type = addr_type;
	ha->refcount = 1;
	ha->global_use = global;
	ha->synced = sync ? 1 : 0;
	ha->sync_cnt = 0;
	list_add_tail_rcu(&ha->list, &list->list);
	list->count++;

	return 0;
}