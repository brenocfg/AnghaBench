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
struct afs_server {int /*<<< orphan*/  usage; } ;
typedef  enum afs_server_trace { ____Placeholder_afs_server_trace } afs_server_trace ;

/* Variables and functions */
 unsigned int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_server (struct afs_server*,unsigned int,int) ; 

struct afs_server *afs_get_server(struct afs_server *server,
				  enum afs_server_trace reason)
{
	unsigned int u = atomic_inc_return(&server->usage);

	trace_afs_server(server, u, reason);
	return server;
}