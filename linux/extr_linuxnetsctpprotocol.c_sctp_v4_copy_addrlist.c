#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_5__ {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct TYPE_6__ {TYPE_2__ v4; } ;
struct sctp_sockaddr_entry {int valid; int /*<<< orphan*/  list; TYPE_3__ a; } ;
struct net_device {int dummy; } ;
struct list_head {int dummy; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_local; struct in_ifaddr* ifa_next; } ;
struct in_device {struct in_ifaddr* ifa_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct in_device* __in_dev_get_rcu (struct net_device*) ; 
 struct sctp_sockaddr_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void sctp_v4_copy_addrlist(struct list_head *addrlist,
				  struct net_device *dev)
{
	struct in_device *in_dev;
	struct in_ifaddr *ifa;
	struct sctp_sockaddr_entry *addr;

	rcu_read_lock();
	if ((in_dev = __in_dev_get_rcu(dev)) == NULL) {
		rcu_read_unlock();
		return;
	}

	for (ifa = in_dev->ifa_list; ifa; ifa = ifa->ifa_next) {
		/* Add the address to the local list.  */
		addr = kzalloc(sizeof(*addr), GFP_ATOMIC);
		if (addr) {
			addr->a.v4.sin_family = AF_INET;
			addr->a.v4.sin_addr.s_addr = ifa->ifa_local;
			addr->valid = 1;
			INIT_LIST_HEAD(&addr->list);
			list_add_tail(&addr->list, addrlist);
		}
	}

	rcu_read_unlock();
}