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
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_clients_exit (struct net*) ; 
 int /*<<< orphan*/  nfs_fs_proc_net_exit (struct net*) ; 

__attribute__((used)) static void nfs_net_exit(struct net *net)
{
	nfs_fs_proc_net_exit(net);
	nfs_clients_exit(net);
}