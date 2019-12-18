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
struct afs_uuid {int dummy; } ;
struct afs_server {int dummy; } ;
struct afs_call {struct afs_server* server; int /*<<< orphan*/  request; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 struct afs_server* afs_find_server_by_uuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int afs_record_cm_probe (struct afs_call*,struct afs_server*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  trace_afs_cm_no_server_u (struct afs_call*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afs_find_cm_server_by_uuid(struct afs_call *call,
				      struct afs_uuid *uuid)
{
	struct afs_server *server;

	rcu_read_lock();
	server = afs_find_server_by_uuid(call->net, call->request);
	rcu_read_unlock();
	if (!server) {
		trace_afs_cm_no_server_u(call, call->request);
		return 0;
	}

	call->server = server;
	return afs_record_cm_probe(call, server);
}