#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct afs_server_list {int nr_servers; TYPE_1__* servers; } ;
struct afs_net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cb_interest; } ;

/* Variables and functions */
 int /*<<< orphan*/  afs_put_cb_interest (struct afs_net*,int /*<<< orphan*/ *) ; 

void afs_clear_callback_interests(struct afs_net *net, struct afs_server_list *slist)
{
	int i;

	for (i = 0; i < slist->nr_servers; i++) {
		afs_put_cb_interest(net, slist->servers[i].cb_interest);
		slist->servers[i].cb_interest = NULL;
	}
}