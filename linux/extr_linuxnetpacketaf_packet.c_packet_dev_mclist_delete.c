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
struct packet_mclist {scalar_t__ ifindex; struct packet_mclist* next; } ;
struct net_device {scalar_t__ ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct packet_mclist*) ; 
 int /*<<< orphan*/  packet_dev_mc (struct net_device*,struct packet_mclist*,int) ; 

__attribute__((used)) static void packet_dev_mclist_delete(struct net_device *dev,
				     struct packet_mclist **mlp)
{
	struct packet_mclist *ml;

	while ((ml = *mlp) != NULL) {
		if (ml->ifindex == dev->ifindex) {
			packet_dev_mc(dev, ml, -1);
			*mlp = ml->next;
			kfree(ml);
		} else
			mlp = &ml->next;
	}
}