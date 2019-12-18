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
struct afs_server {int /*<<< orphan*/  usage; int /*<<< orphan*/  put_time; } ;
struct afs_net {int dummy; } ;
typedef  enum afs_server_trace { ____Placeholder_afs_server_trace } afs_server_trace ;

/* Variables and functions */
 int /*<<< orphan*/  afs_server_gc_delay ; 
 int /*<<< orphan*/  afs_set_server_timer (struct afs_net*,int /*<<< orphan*/ ) ; 
 unsigned int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  trace_afs_server (struct afs_server*,unsigned int,int) ; 

void afs_put_server(struct afs_net *net, struct afs_server *server,
		    enum afs_server_trace reason)
{
	unsigned int usage;

	if (!server)
		return;

	server->put_time = ktime_get_real_seconds();

	usage = atomic_dec_return(&server->usage);

	trace_afs_server(server, usage, reason);

	if (likely(usage > 0))
		return;

	afs_set_server_timer(net, afs_server_gc_delay);
}