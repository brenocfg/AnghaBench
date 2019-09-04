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
struct fuse_conn {int /*<<< orphan*/  num_waiting; } ;

/* Variables and functions */
 int /*<<< orphan*/  FR_ISREPLY ; 
 int /*<<< orphan*/  FR_WAITING ; 
 int /*<<< orphan*/  __fuse_request_send (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fuse_request_send(struct fuse_conn *fc, struct fuse_req *req)
{
	__set_bit(FR_ISREPLY, &req->flags);
	if (!test_bit(FR_WAITING, &req->flags)) {
		__set_bit(FR_WAITING, &req->flags);
		atomic_inc(&fc->num_waiting);
	}
	__fuse_request_send(fc, req);
}