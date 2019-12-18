#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int in_numargs; int out_numargs; int out_argvar; int force; int nocreds; int /*<<< orphan*/  (* end ) (struct fuse_conn*,TYPE_6__*,int /*<<< orphan*/ ) ;TYPE_5__* out_args; TYPE_3__* in_args; int /*<<< orphan*/  opcode; } ;
struct TYPE_11__ {int max_readahead; int flags; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct fuse_init_args {TYPE_6__ args; int /*<<< orphan*/  out; TYPE_4__ in; } ;
struct fuse_conn {TYPE_2__* sb; } ;
struct TYPE_12__ {int size; int /*<<< orphan*/ * value; } ;
struct TYPE_10__ {int size; TYPE_4__* value; } ;
struct TYPE_9__ {TYPE_1__* s_bdi; } ;
struct TYPE_8__ {int ra_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTCONN ; 
 int FUSE_ABORT_ERROR ; 
 int FUSE_ASYNC_DIO ; 
 int FUSE_ASYNC_READ ; 
 int FUSE_ATOMIC_O_TRUNC ; 
 int FUSE_AUTO_INVAL_DATA ; 
 int FUSE_BIG_WRITES ; 
 int FUSE_CACHE_SYMLINKS ; 
 int FUSE_DONT_MASK ; 
 int FUSE_DO_READDIRPLUS ; 
 int FUSE_EXPLICIT_INVAL_DATA ; 
 int FUSE_EXPORT_SUPPORT ; 
 int FUSE_FLOCK_LOCKS ; 
 int FUSE_HANDLE_KILLPRIV ; 
 int FUSE_HAS_IOCTL_DIR ; 
 int /*<<< orphan*/  FUSE_INIT ; 
 int /*<<< orphan*/  FUSE_KERNEL_MINOR_VERSION ; 
 int /*<<< orphan*/  FUSE_KERNEL_VERSION ; 
 int FUSE_MAX_PAGES ; 
 int FUSE_NO_OPENDIR_SUPPORT ; 
 int FUSE_NO_OPEN_SUPPORT ; 
 int FUSE_PARALLEL_DIROPS ; 
 int FUSE_POSIX_ACL ; 
 int FUSE_POSIX_LOCKS ; 
 int FUSE_READDIRPLUS_AUTO ; 
 int FUSE_SPLICE_MOVE ; 
 int FUSE_SPLICE_READ ; 
 int FUSE_SPLICE_WRITE ; 
 int FUSE_WRITEBACK_CACHE ; 
 int GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int __GFP_NOFAIL ; 
 scalar_t__ fuse_simple_background (struct fuse_conn*,TYPE_6__*,int) ; 
 struct fuse_init_args* kzalloc (int,int) ; 
 int /*<<< orphan*/  process_init_reply (struct fuse_conn*,TYPE_6__*,int /*<<< orphan*/ ) ; 

void fuse_send_init(struct fuse_conn *fc)
{
	struct fuse_init_args *ia;

	ia = kzalloc(sizeof(*ia), GFP_KERNEL | __GFP_NOFAIL);

	ia->in.major = FUSE_KERNEL_VERSION;
	ia->in.minor = FUSE_KERNEL_MINOR_VERSION;
	ia->in.max_readahead = fc->sb->s_bdi->ra_pages * PAGE_SIZE;
	ia->in.flags |=
		FUSE_ASYNC_READ | FUSE_POSIX_LOCKS | FUSE_ATOMIC_O_TRUNC |
		FUSE_EXPORT_SUPPORT | FUSE_BIG_WRITES | FUSE_DONT_MASK |
		FUSE_SPLICE_WRITE | FUSE_SPLICE_MOVE | FUSE_SPLICE_READ |
		FUSE_FLOCK_LOCKS | FUSE_HAS_IOCTL_DIR | FUSE_AUTO_INVAL_DATA |
		FUSE_DO_READDIRPLUS | FUSE_READDIRPLUS_AUTO | FUSE_ASYNC_DIO |
		FUSE_WRITEBACK_CACHE | FUSE_NO_OPEN_SUPPORT |
		FUSE_PARALLEL_DIROPS | FUSE_HANDLE_KILLPRIV | FUSE_POSIX_ACL |
		FUSE_ABORT_ERROR | FUSE_MAX_PAGES | FUSE_CACHE_SYMLINKS |
		FUSE_NO_OPENDIR_SUPPORT | FUSE_EXPLICIT_INVAL_DATA;
	ia->args.opcode = FUSE_INIT;
	ia->args.in_numargs = 1;
	ia->args.in_args[0].size = sizeof(ia->in);
	ia->args.in_args[0].value = &ia->in;
	ia->args.out_numargs = 1;
	/* Variable length argument used for backward compatibility
	   with interface version < 7.5.  Rest of init_out is zeroed
	   by do_get_request(), so a short reply is not a problem */
	ia->args.out_argvar = 1;
	ia->args.out_args[0].size = sizeof(ia->out);
	ia->args.out_args[0].value = &ia->out;
	ia->args.force = true;
	ia->args.nocreds = true;
	ia->args.end = process_init_reply;

	if (fuse_simple_background(fc, &ia->args, GFP_KERNEL) != 0)
		process_init_reply(fc, &ia->args, -ENOTCONN);
}