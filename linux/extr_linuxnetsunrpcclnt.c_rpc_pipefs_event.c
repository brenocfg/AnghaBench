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
struct super_block {int /*<<< orphan*/  s_fs_info; } ;
struct rpc_clnt {int dummy; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int __rpc_pipefs_event (struct rpc_clnt*,unsigned long,struct super_block*) ; 
 struct rpc_clnt* rpc_get_client_for_event (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int rpc_pipefs_event(struct notifier_block *nb, unsigned long event,
			    void *ptr)
{
	struct super_block *sb = ptr;
	struct rpc_clnt *clnt;
	int error = 0;

	while ((clnt = rpc_get_client_for_event(sb->s_fs_info, event))) {
		error = __rpc_pipefs_event(clnt, event, sb);
		if (error)
			break;
	}
	return error;
}