#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct fuse_open_in {int dummy; } ;
struct fuse_conn {int minor; } ;
struct TYPE_8__ {int opcode; } ;
struct TYPE_10__ {TYPE_4__* args; TYPE_3__ h; } ;
struct TYPE_7__ {TYPE_1__* args; } ;
struct fuse_args {TYPE_5__ in; TYPE_2__ out; } ;
struct TYPE_9__ {int size; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_COMPAT_ATTR_OUT_SIZE ; 
 int /*<<< orphan*/  FUSE_COMPAT_ENTRY_OUT_SIZE ; 
 int FUSE_COMPAT_MKNOD_IN_SIZE ; 
 int /*<<< orphan*/  FUSE_COMPAT_STATFS_SIZE ; 
#define  FUSE_CREATE 135 
#define  FUSE_GETATTR 134 
#define  FUSE_LINK 133 
#define  FUSE_LOOKUP 132 
#define  FUSE_MKDIR 131 
#define  FUSE_MKNOD 130 
#define  FUSE_SETATTR 129 
 int FUSE_STATFS ; 
#define  FUSE_SYMLINK 128 

__attribute__((used)) static void fuse_adjust_compat(struct fuse_conn *fc, struct fuse_args *args)
{
	if (fc->minor < 4 && args->in.h.opcode == FUSE_STATFS)
		args->out.args[0].size = FUSE_COMPAT_STATFS_SIZE;

	if (fc->minor < 9) {
		switch (args->in.h.opcode) {
		case FUSE_LOOKUP:
		case FUSE_CREATE:
		case FUSE_MKNOD:
		case FUSE_MKDIR:
		case FUSE_SYMLINK:
		case FUSE_LINK:
			args->out.args[0].size = FUSE_COMPAT_ENTRY_OUT_SIZE;
			break;
		case FUSE_GETATTR:
		case FUSE_SETATTR:
			args->out.args[0].size = FUSE_COMPAT_ATTR_OUT_SIZE;
			break;
		}
	}
	if (fc->minor < 12) {
		switch (args->in.h.opcode) {
		case FUSE_CREATE:
			args->in.args[0].size = sizeof(struct fuse_open_in);
			break;
		case FUSE_MKNOD:
			args->in.args[0].size = FUSE_COMPAT_MKNOD_IN_SIZE;
			break;
		}
	}
}