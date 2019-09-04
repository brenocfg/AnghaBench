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
typedef  int /*<<< orphan*/  u_int16_t ;
struct netns_proto_gre {int /*<<< orphan*/ * gre_timeouts; int /*<<< orphan*/  keymap_list; int /*<<< orphan*/  keymap_lock; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int GRE_CT_MAX ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct netns_proto_gre* gre_pernet (struct net*) ; 
 int /*<<< orphan*/ * gre_timeouts ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gre_init_net(struct net *net, u_int16_t proto)
{
	struct netns_proto_gre *net_gre = gre_pernet(net);
	int i;

	rwlock_init(&net_gre->keymap_lock);
	INIT_LIST_HEAD(&net_gre->keymap_list);
	for (i = 0; i < GRE_CT_MAX; i++)
		net_gre->gre_timeouts[i] = gre_timeouts[i];

	return 0;
}