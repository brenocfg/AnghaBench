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
struct pneigh_entry {struct pneigh_entry* next; struct net_device* dev; int /*<<< orphan*/  key; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,void const*,unsigned int) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  pneigh_net (struct pneigh_entry*) ; 

__attribute__((used)) static struct pneigh_entry *__pneigh_lookup_1(struct pneigh_entry *n,
					      struct net *net,
					      const void *pkey,
					      unsigned int key_len,
					      struct net_device *dev)
{
	while (n) {
		if (!memcmp(n->key, pkey, key_len) &&
		    net_eq(pneigh_net(n), net) &&
		    (n->dev == dev || !n->dev))
			return n;
		n = n->next;
	}
	return NULL;
}