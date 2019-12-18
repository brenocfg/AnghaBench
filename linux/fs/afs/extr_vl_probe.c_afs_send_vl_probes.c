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
struct key {int dummy; } ;
struct afs_vlserver_list {int nr_servers; TYPE_1__* servers; } ;
struct afs_vlserver {int /*<<< orphan*/  flags; } ;
struct afs_net {int dummy; } ;
struct afs_error {int error; int responded; } ;
struct TYPE_2__ {struct afs_vlserver* server; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VLSERVER_FL_PROBED ; 
 int /*<<< orphan*/  AFS_VLSERVER_FL_PROBING ; 
 scalar_t__ afs_do_probe_vlserver (struct afs_net*,struct afs_vlserver*,struct key*,int,struct afs_error*) ; 
 int /*<<< orphan*/  test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int afs_send_vl_probes(struct afs_net *net, struct key *key,
		       struct afs_vlserver_list *vllist)
{
	struct afs_vlserver *server;
	struct afs_error e;
	bool in_progress = false;
	int i;

	e.error = 0;
	e.responded = false;
	for (i = 0; i < vllist->nr_servers; i++) {
		server = vllist->servers[i].server;
		if (test_bit(AFS_VLSERVER_FL_PROBED, &server->flags))
			continue;

		if (!test_and_set_bit_lock(AFS_VLSERVER_FL_PROBING, &server->flags) &&
		    afs_do_probe_vlserver(net, server, key, i, &e))
			in_progress = true;
	}

	return in_progress ? 0 : e.error;
}