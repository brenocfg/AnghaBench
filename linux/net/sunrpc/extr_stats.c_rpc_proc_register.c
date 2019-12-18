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
struct rpc_stat {TYPE_1__* program; } ;
struct proc_dir_entry {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct proc_dir_entry* do_register (struct net*,int /*<<< orphan*/ ,struct rpc_stat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_proc_fops ; 

struct proc_dir_entry *
rpc_proc_register(struct net *net, struct rpc_stat *statp)
{
	return do_register(net, statp->program->name, statp, &rpc_proc_fops);
}