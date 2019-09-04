#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  inode; } ;
struct TYPE_7__ {TYPE_1__ release; } ;
struct fuse_req {int /*<<< orphan*/  flags; int /*<<< orphan*/  end; TYPE_2__ misc; } ;
struct fuse_file {TYPE_3__* fc; struct fuse_req* reserved_req; int /*<<< orphan*/  count; } ;
struct TYPE_8__ {scalar_t__ no_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  FR_BACKGROUND ; 
 int /*<<< orphan*/  FR_FORCE ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_put_request (TYPE_3__*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_release_end ; 
 int /*<<< orphan*/  fuse_request_send (TYPE_3__*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_request_send_background (TYPE_3__*,struct fuse_req*) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fuse_file*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_file_put(struct fuse_file *ff, bool sync, bool isdir)
{
	if (refcount_dec_and_test(&ff->count)) {
		struct fuse_req *req = ff->reserved_req;

		if (ff->fc->no_open && !isdir) {
			/*
			 * Drop the release request when client does not
			 * implement 'open'
			 */
			__clear_bit(FR_BACKGROUND, &req->flags);
			iput(req->misc.release.inode);
			fuse_put_request(ff->fc, req);
		} else if (sync) {
			__set_bit(FR_FORCE, &req->flags);
			__clear_bit(FR_BACKGROUND, &req->flags);
			fuse_request_send(ff->fc, req);
			iput(req->misc.release.inode);
			fuse_put_request(ff->fc, req);
		} else {
			req->end = fuse_release_end;
			__set_bit(FR_BACKGROUND, &req->flags);
			fuse_request_send_background(ff->fc, req);
		}
		kfree(ff);
	}
}