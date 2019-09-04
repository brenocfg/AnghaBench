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
struct TYPE_13__ {scalar_t__ error; } ;
struct TYPE_15__ {int numargs; TYPE_8__* args; TYPE_5__ h; scalar_t__ argvar; } ;
struct TYPE_9__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_11__ {int numargs; TYPE_8__* args; TYPE_1__ h; } ;
struct fuse_req {TYPE_7__ out; TYPE_3__ in; } ;
struct fuse_in_arg {int dummy; } ;
struct fuse_conn {int dummy; } ;
struct TYPE_14__ {int numargs; scalar_t__ argvar; int /*<<< orphan*/  args; } ;
struct TYPE_10__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_12__ {int numargs; int /*<<< orphan*/  args; TYPE_2__ h; } ;
struct fuse_args {TYPE_6__ out; TYPE_4__ in; } ;
struct fuse_arg {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_16__ {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 scalar_t__ PTR_ERR (struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_adjust_compat (struct fuse_conn*,struct fuse_args*) ; 
 struct fuse_req* fuse_get_req (struct fuse_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_request_send (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  memcpy (TYPE_8__*,int /*<<< orphan*/ ,int) ; 

ssize_t fuse_simple_request(struct fuse_conn *fc, struct fuse_args *args)
{
	struct fuse_req *req;
	ssize_t ret;

	req = fuse_get_req(fc, 0);
	if (IS_ERR(req))
		return PTR_ERR(req);

	/* Needs to be done after fuse_get_req() so that fc->minor is valid */
	fuse_adjust_compat(fc, args);

	req->in.h.opcode = args->in.h.opcode;
	req->in.h.nodeid = args->in.h.nodeid;
	req->in.numargs = args->in.numargs;
	memcpy(req->in.args, args->in.args,
	       args->in.numargs * sizeof(struct fuse_in_arg));
	req->out.argvar = args->out.argvar;
	req->out.numargs = args->out.numargs;
	memcpy(req->out.args, args->out.args,
	       args->out.numargs * sizeof(struct fuse_arg));
	fuse_request_send(fc, req);
	ret = req->out.h.error;
	if (!ret && args->out.argvar) {
		BUG_ON(args->out.numargs != 1);
		ret = req->out.args[0].size;
	}
	fuse_put_request(fc, req);

	return ret;
}