#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int id; int /*<<< orphan*/  orangefs_config_server; int /*<<< orphan*/  fs_id; } ;
struct TYPE_6__ {TYPE_1__ fs_umount; } ;
struct TYPE_5__ {TYPE_3__ req; } ;
struct orangefs_kernel_op_s {TYPE_2__ upcall; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ ORANGEFS_MAX_SERVER_ADDR_LEN ; 
 int /*<<< orphan*/  ORANGEFS_VFS_OP_FS_UMOUNT ; 
 int /*<<< orphan*/  gossip_err (char*,int) ; 
 struct orangefs_kernel_op_s* op_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_release (struct orangefs_kernel_op_s*) ; 
 int service_operation (struct orangefs_kernel_op_s*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

__attribute__((used)) static int orangefs_unmount(int id, __s32 fs_id, const char *devname)
{
	struct orangefs_kernel_op_s *op;
	int r;
	op = op_alloc(ORANGEFS_VFS_OP_FS_UMOUNT);
	if (!op)
		return -ENOMEM;
	op->upcall.req.fs_umount.id = id;
	op->upcall.req.fs_umount.fs_id = fs_id;
	strncpy(op->upcall.req.fs_umount.orangefs_config_server,
	    devname, ORANGEFS_MAX_SERVER_ADDR_LEN - 1);
	r = service_operation(op, "orangefs_fs_umount", 0);
	/* Not much to do about an error here. */
	if (r)
		gossip_err("orangefs_unmount: service_operation %d\n", r);
	op_release(op);
	return r;
}