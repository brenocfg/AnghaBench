#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ip; } ;
struct TYPE_6__ {TYPE_1__ u3; } ;
struct nf_conntrack_tuple {TYPE_2__ dst; } ;
struct nf_conn {TYPE_4__* tuplehash; } ;
struct net_device {scalar_t__ ifindex; } ;
struct in_ifaddr {scalar_t__ ifa_address; TYPE_3__* ifa_dev; } ;
struct TYPE_8__ {struct nf_conntrack_tuple tuple; } ;
struct TYPE_7__ {struct net_device* dev; } ;

/* Variables and functions */
 size_t IP_CT_DIR_REPLY ; 
 int /*<<< orphan*/  device_cmp (struct nf_conn*,void*) ; 

__attribute__((used)) static int inet_cmp(struct nf_conn *ct, void *ptr)
{
	struct in_ifaddr *ifa = (struct in_ifaddr *)ptr;
	struct net_device *dev = ifa->ifa_dev->dev;
	struct nf_conntrack_tuple *tuple;

	if (!device_cmp(ct, (void *)(long)dev->ifindex))
		return 0;

	tuple = &ct->tuplehash[IP_CT_DIR_REPLY].tuple;

	return ifa->ifa_address == tuple->dst.u3.ip;
}