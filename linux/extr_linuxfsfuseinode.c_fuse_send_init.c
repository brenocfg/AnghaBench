#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct fuse_init_in {int max_readahead; int flags; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_16__ {int /*<<< orphan*/  init_out; struct fuse_init_in init_in; } ;
struct TYPE_15__ {int numargs; int argvar; TYPE_6__* args; } ;
struct TYPE_11__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_13__ {int numargs; TYPE_4__* args; TYPE_3__ h; } ;
struct fuse_req {int /*<<< orphan*/  end; TYPE_8__ misc; TYPE_7__ out; TYPE_5__ in; } ;
struct fuse_init_out {int dummy; } ;
struct fuse_conn {TYPE_2__* sb; } ;
struct TYPE_14__ {int size; int /*<<< orphan*/ * value; } ;
struct TYPE_12__ {int size; struct fuse_init_in* value; } ;
struct TYPE_10__ {TYPE_1__* s_bdi; } ;
struct TYPE_9__ {int ra_pages; } ;

/* Variables and functions */
 int FUSE_ABORT_ERROR ; 
 int FUSE_ASYNC_DIO ; 
 int FUSE_ASYNC_READ ; 
 int FUSE_ATOMIC_O_TRUNC ; 
 int FUSE_AUTO_INVAL_DATA ; 
 int FUSE_BIG_WRITES ; 
 int FUSE_DONT_MASK ; 
 int FUSE_DO_READDIRPLUS ; 
 int FUSE_EXPORT_SUPPORT ; 
 int FUSE_FLOCK_LOCKS ; 
 int FUSE_HANDLE_KILLPRIV ; 
 int FUSE_HAS_IOCTL_DIR ; 
 int /*<<< orphan*/  FUSE_INIT ; 
 int /*<<< orphan*/  FUSE_KERNEL_MINOR_VERSION ; 
 int /*<<< orphan*/  FUSE_KERNEL_VERSION ; 
 int FUSE_NO_OPEN_SUPPORT ; 
 int FUSE_PARALLEL_DIROPS ; 
 int FUSE_POSIX_ACL ; 
 int FUSE_POSIX_LOCKS ; 
 int FUSE_READDIRPLUS_AUTO ; 
 int FUSE_SPLICE_MOVE ; 
 int FUSE_SPLICE_READ ; 
 int FUSE_SPLICE_WRITE ; 
 int FUSE_WRITEBACK_CACHE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  fuse_request_send_background (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  process_init_reply ; 

__attribute__((used)) static void fuse_send_init(struct fuse_conn *fc, struct fuse_req *req)
{
	struct fuse_init_in *arg = &req->misc.init_in;

	arg->major = FUSE_KERNEL_VERSION;
	arg->minor = FUSE_KERNEL_MINOR_VERSION;
	arg->max_readahead = fc->sb->s_bdi->ra_pages * PAGE_SIZE;
	arg->flags |= FUSE_ASYNC_READ | FUSE_POSIX_LOCKS | FUSE_ATOMIC_O_TRUNC |
		FUSE_EXPORT_SUPPORT | FUSE_BIG_WRITES | FUSE_DONT_MASK |
		FUSE_SPLICE_WRITE | FUSE_SPLICE_MOVE | FUSE_SPLICE_READ |
		FUSE_FLOCK_LOCKS | FUSE_HAS_IOCTL_DIR | FUSE_AUTO_INVAL_DATA |
		FUSE_DO_READDIRPLUS | FUSE_READDIRPLUS_AUTO | FUSE_ASYNC_DIO |
		FUSE_WRITEBACK_CACHE | FUSE_NO_OPEN_SUPPORT |
		FUSE_PARALLEL_DIROPS | FUSE_HANDLE_KILLPRIV | FUSE_POSIX_ACL |
		FUSE_ABORT_ERROR;
	req->in.h.opcode = FUSE_INIT;
	req->in.numargs = 1;
	req->in.args[0].size = sizeof(*arg);
	req->in.args[0].value = arg;
	req->out.numargs = 1;
	/* Variable length argument used for backward compatibility
	   with interface version < 7.5.  Rest of init_out is zeroed
	   by do_get_request(), so a short reply is not a problem */
	req->out.argvar = 1;
	req->out.args[0].size = sizeof(struct fuse_init_out);
	req->out.args[0].value = &req->misc.init_out;
	req->end = process_init_reply;
	fuse_request_send_background(fc, req);
}