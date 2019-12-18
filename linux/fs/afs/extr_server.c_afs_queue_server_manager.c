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
struct afs_net {int /*<<< orphan*/  fs_manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  afs_dec_servers_outstanding (struct afs_net*) ; 
 int /*<<< orphan*/  afs_inc_servers_outstanding (struct afs_net*) ; 
 int /*<<< orphan*/  afs_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afs_queue_server_manager(struct afs_net *net)
{
	afs_inc_servers_outstanding(net);
	if (!queue_work(afs_wq, &net->fs_manager))
		afs_dec_servers_outstanding(net);
}