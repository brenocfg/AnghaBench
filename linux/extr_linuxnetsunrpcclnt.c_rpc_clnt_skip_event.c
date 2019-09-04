#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pdh_dentry; } ;
struct rpc_clnt {TYPE_2__ cl_pipedir_objects; int /*<<< orphan*/  cl_count; TYPE_1__* cl_program; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pipe_dir_name; } ;

/* Variables and functions */
#define  RPC_PIPEFS_MOUNT 129 
#define  RPC_PIPEFS_UMOUNT 128 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rpc_clnt_skip_event(struct rpc_clnt *clnt, unsigned long event)
{
	if (clnt->cl_program->pipe_dir_name == NULL)
		return 1;

	switch (event) {
	case RPC_PIPEFS_MOUNT:
		if (clnt->cl_pipedir_objects.pdh_dentry != NULL)
			return 1;
		if (atomic_read(&clnt->cl_count) == 0)
			return 1;
		break;
	case RPC_PIPEFS_UMOUNT:
		if (clnt->cl_pipedir_objects.pdh_dentry == NULL)
			return 1;
		break;
	}
	return 0;
}