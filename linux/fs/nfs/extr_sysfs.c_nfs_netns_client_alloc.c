#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kset; } ;
struct nfs_netns_client {TYPE_1__ kobject; struct net* net; } ;
struct net {int dummy; } ;
struct kobject {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kobject_init_and_add (TYPE_1__*,int /*<<< orphan*/ *,struct kobject*,char*) ; 
 int /*<<< orphan*/  kobject_put (TYPE_1__*) ; 
 struct nfs_netns_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_client_kset ; 
 int /*<<< orphan*/  nfs_netns_client_type ; 

__attribute__((used)) static struct nfs_netns_client *nfs_netns_client_alloc(struct kobject *parent,
		struct net *net)
{
	struct nfs_netns_client *p;

	p = kzalloc(sizeof(*p), GFP_KERNEL);
	if (p) {
		p->net = net;
		p->kobject.kset = nfs_client_kset;
		if (kobject_init_and_add(&p->kobject, &nfs_netns_client_type,
					parent, "nfs_client") == 0)
			return p;
		kobject_put(&p->kobject);
	}
	return NULL;
}