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
struct afs_server_list {int nr_servers; TYPE_1__* servers; int /*<<< orphan*/  usage; } ;
struct afs_net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  server; int /*<<< orphan*/  cb_interest; } ;

/* Variables and functions */
 int /*<<< orphan*/  afs_put_cb_interest (struct afs_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_put_server (struct afs_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_server_trace_put_slist ; 
 int /*<<< orphan*/  kfree (struct afs_server_list*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void afs_put_serverlist(struct afs_net *net, struct afs_server_list *slist)
{
	int i;

	if (slist && refcount_dec_and_test(&slist->usage)) {
		for (i = 0; i < slist->nr_servers; i++) {
			afs_put_cb_interest(net, slist->servers[i].cb_interest);
			afs_put_server(net, slist->servers[i].server,
				       afs_server_trace_put_slist);
		}
		kfree(slist);
	}
}