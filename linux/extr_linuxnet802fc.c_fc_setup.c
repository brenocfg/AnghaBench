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
struct net_device {int mtu; int tx_queue_len; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/ * header_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IEEE802 ; 
 int /*<<< orphan*/  FC_ALEN ; 
 int /*<<< orphan*/  FC_HLEN ; 
 int /*<<< orphan*/  IFF_BROADCAST ; 
 int /*<<< orphan*/  fc_header_ops ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_setup(struct net_device *dev)
{
	dev->header_ops		= &fc_header_ops;
	dev->type		= ARPHRD_IEEE802;
	dev->hard_header_len	= FC_HLEN;
	dev->mtu		= 2024;
	dev->addr_len		= FC_ALEN;
	dev->tx_queue_len	= 100; /* Long queues on fc */
	dev->flags		= IFF_BROADCAST;

	memset(dev->broadcast, 0xFF, FC_ALEN);
}