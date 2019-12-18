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
struct datalink_proto {unsigned char* type; int header_length; int /*<<< orphan*/  sap; int /*<<< orphan*/  request; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (struct datalink_proto*) ; 
 struct datalink_proto* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_sap_open (unsigned char,int (*) (struct sk_buff*,struct net_device*,struct packet_type*,struct net_device*)) ; 
 int /*<<< orphan*/  p8022_request ; 

struct datalink_proto *register_8022_client(unsigned char type,
					    int (*func)(struct sk_buff *skb,
							struct net_device *dev,
							struct packet_type *pt,
							struct net_device *orig_dev))
{
	struct datalink_proto *proto;

	proto = kmalloc(sizeof(*proto), GFP_ATOMIC);
	if (proto) {
		proto->type[0]		= type;
		proto->header_length	= 3;
		proto->request		= p8022_request;
		proto->sap = llc_sap_open(type, func);
		if (!proto->sap) {
			kfree(proto);
			proto = NULL;
		}
	}
	return proto;
}