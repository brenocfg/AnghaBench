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
struct net_device {int tx_queue_len; int* broadcast; int flags; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  mtu; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_LOCALTLK ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_NOARP ; 
 int /*<<< orphan*/  LTALK_ALEN ; 
 int /*<<< orphan*/  LTALK_HLEN ; 
 int /*<<< orphan*/  LTALK_MTU ; 

__attribute__((used)) static void ltalk_setup(struct net_device *dev)
{
	/* Fill in the fields of the device structure with localtalk-generic values. */

	dev->type		= ARPHRD_LOCALTLK;
	dev->hard_header_len 	= LTALK_HLEN;
	dev->mtu		= LTALK_MTU;
	dev->addr_len		= LTALK_ALEN;
	dev->tx_queue_len	= 10;

	dev->broadcast[0]	= 0xFF;

	dev->flags		= IFF_BROADCAST|IFF_MULTICAST|IFF_NOARP;
}