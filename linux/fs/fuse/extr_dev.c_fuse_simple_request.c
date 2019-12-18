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
struct TYPE_4__ {scalar_t__ error; } ;
struct TYPE_5__ {TYPE_1__ h; } ;
struct fuse_req {TYPE_2__ out; int /*<<< orphan*/  flags; } ;
struct fuse_conn {int /*<<< orphan*/  num_waiting; } ;
struct fuse_args {int out_numargs; TYPE_3__* out_args; scalar_t__ out_argvar; int /*<<< orphan*/  noreply; int /*<<< orphan*/  nocreds; scalar_t__ force; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_6__ {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  FR_FORCE ; 
 int /*<<< orphan*/  FR_ISREPLY ; 
 int /*<<< orphan*/  FR_WAITING ; 
 int GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 scalar_t__ PTR_ERR (struct fuse_req*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  __fuse_request_send (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_adjust_compat (struct fuse_conn*,struct fuse_args*) ; 
 int /*<<< orphan*/  fuse_args_to_req (struct fuse_req*,struct fuse_args*) ; 
 int /*<<< orphan*/  fuse_force_creds (struct fuse_conn*,struct fuse_req*) ; 
 struct fuse_req* fuse_get_req (struct fuse_conn*,int) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 struct fuse_req* fuse_request_alloc (int) ; 

ssize_t fuse_simple_request(struct fuse_conn *fc, struct fuse_args *args)
{
	struct fuse_req *req;
	ssize_t ret;

	if (args->force) {
		atomic_inc(&fc->num_waiting);
		req = fuse_request_alloc(GFP_KERNEL | __GFP_NOFAIL);

		if (!args->nocreds)
			fuse_force_creds(fc, req);

		__set_bit(FR_WAITING, &req->flags);
		__set_bit(FR_FORCE, &req->flags);
	} else {
		WARN_ON(args->nocreds);
		req = fuse_get_req(fc, false);
		if (IS_ERR(req))
			return PTR_ERR(req);
	}

	/* Needs to be done after fuse_get_req() so that fc->minor is valid */
	fuse_adjust_compat(fc, args);
	fuse_args_to_req(req, args);

	if (!args->noreply)
		__set_bit(FR_ISREPLY, &req->flags);
	__fuse_request_send(fc, req);
	ret = req->out.h.error;
	if (!ret && args->out_argvar) {
		BUG_ON(args->out_numargs == 0);
		ret = args->out_args[args->out_numargs - 1].size;
	}
	fuse_put_request(fc, req);

	return ret;
}