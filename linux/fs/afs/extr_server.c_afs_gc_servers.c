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
struct afs_server {int /*<<< orphan*/  addr6_link; int /*<<< orphan*/  addr4_link; int /*<<< orphan*/  proc_link; int /*<<< orphan*/  uuid_rb; int /*<<< orphan*/  usage; struct afs_server* gc_next; } ;
struct afs_net {int /*<<< orphan*/  fs_addr_lock; int /*<<< orphan*/  fs_lock; int /*<<< orphan*/  fs_servers; } ;

/* Variables and functions */
 int /*<<< orphan*/  afs_destroy_server (struct afs_net*,struct afs_server*) ; 
 int /*<<< orphan*/  afs_server_trace_gc ; 
 int atomic_try_cmpxchg (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_server (struct afs_server*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afs_gc_servers(struct afs_net *net, struct afs_server *gc_list)
{
	struct afs_server *server;
	bool deleted;
	int usage;

	while ((server = gc_list)) {
		gc_list = server->gc_next;

		write_seqlock(&net->fs_lock);
		usage = 1;
		deleted = atomic_try_cmpxchg(&server->usage, &usage, 0);
		trace_afs_server(server, usage, afs_server_trace_gc);
		if (deleted) {
			rb_erase(&server->uuid_rb, &net->fs_servers);
			hlist_del_rcu(&server->proc_link);
		}
		write_sequnlock(&net->fs_lock);

		if (deleted) {
			write_seqlock(&net->fs_addr_lock);
			if (!hlist_unhashed(&server->addr4_link))
				hlist_del_rcu(&server->addr4_link);
			if (!hlist_unhashed(&server->addr6_link))
				hlist_del_rcu(&server->addr6_link);
			write_sequnlock(&net->fs_addr_lock);
			afs_destroy_server(net, server);
		}
	}
}