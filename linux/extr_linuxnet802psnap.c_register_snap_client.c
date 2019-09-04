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
struct datalink_proto {int (* rcvfunc ) (struct sk_buff*,struct net_device*,struct packet_type*,struct net_device*) ;int header_length; int /*<<< orphan*/  node; int /*<<< orphan*/  request; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ find_snap_client (unsigned char const*) ; 
 struct datalink_proto* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  snap_list ; 
 int /*<<< orphan*/  snap_lock ; 
 int /*<<< orphan*/  snap_request ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct datalink_proto *register_snap_client(const unsigned char *desc,
					    int (*rcvfunc)(struct sk_buff *,
							   struct net_device *,
							   struct packet_type *,
							   struct net_device *))
{
	struct datalink_proto *proto = NULL;

	spin_lock_bh(&snap_lock);

	if (find_snap_client(desc))
		goto out;

	proto = kmalloc(sizeof(*proto), GFP_ATOMIC);
	if (proto) {
		memcpy(proto->type, desc, 5);
		proto->rcvfunc		= rcvfunc;
		proto->header_length	= 5 + 3; /* snap + 802.2 */
		proto->request		= snap_request;
		list_add_rcu(&proto->node, &snap_list);
	}
out:
	spin_unlock_bh(&snap_lock);

	return proto;
}