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
struct fuse_req {int /*<<< orphan*/  flags; } ;
struct fuse_conn {int dummy; } ;
struct fuse_args {int nocreds; scalar_t__ force; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  FR_BACKGROUND ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 int PTR_ERR (struct fuse_req*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_args_to_req (struct fuse_req*,struct fuse_args*) ; 
 struct fuse_req* fuse_get_req (struct fuse_conn*,int) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 struct fuse_req* fuse_request_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_request_queue_background (struct fuse_conn*,struct fuse_req*) ; 

int fuse_simple_background(struct fuse_conn *fc, struct fuse_args *args,
			    gfp_t gfp_flags)
{
	struct fuse_req *req;

	if (args->force) {
		WARN_ON(!args->nocreds);
		req = fuse_request_alloc(gfp_flags);
		if (!req)
			return -ENOMEM;
		__set_bit(FR_BACKGROUND, &req->flags);
	} else {
		WARN_ON(args->nocreds);
		req = fuse_get_req(fc, true);
		if (IS_ERR(req))
			return PTR_ERR(req);
	}

	fuse_args_to_req(req, args);

	if (!fuse_request_queue_background(fc, req)) {
		fuse_put_request(fc, req);
		return -ENOTCONN;
	}

	return 0;
}