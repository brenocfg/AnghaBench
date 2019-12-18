#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fuse_req {int /*<<< orphan*/  list; int /*<<< orphan*/  flags; } ;
struct fuse_conn {scalar_t__ num_background; scalar_t__ max_background; int blocked; scalar_t__ congestion_threshold; int /*<<< orphan*/  bg_lock; int /*<<< orphan*/  bg_queue; TYPE_1__* sb; int /*<<< orphan*/  connected; int /*<<< orphan*/  num_waiting; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_bdi; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 int /*<<< orphan*/  BLK_RW_SYNC ; 
 int /*<<< orphan*/  FR_BACKGROUND ; 
 int /*<<< orphan*/  FR_ISREPLY ; 
 int /*<<< orphan*/  FR_WAITING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_bg_queue (struct fuse_conn*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bdi_congested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool fuse_request_queue_background(struct fuse_conn *fc,
					  struct fuse_req *req)
{
	bool queued = false;

	WARN_ON(!test_bit(FR_BACKGROUND, &req->flags));
	if (!test_bit(FR_WAITING, &req->flags)) {
		__set_bit(FR_WAITING, &req->flags);
		atomic_inc(&fc->num_waiting);
	}
	__set_bit(FR_ISREPLY, &req->flags);
	spin_lock(&fc->bg_lock);
	if (likely(fc->connected)) {
		fc->num_background++;
		if (fc->num_background == fc->max_background)
			fc->blocked = 1;
		if (fc->num_background == fc->congestion_threshold && fc->sb) {
			set_bdi_congested(fc->sb->s_bdi, BLK_RW_SYNC);
			set_bdi_congested(fc->sb->s_bdi, BLK_RW_ASYNC);
		}
		list_add_tail(&req->list, &fc->bg_queue);
		flush_bg_queue(fc);
		queued = true;
	}
	spin_unlock(&fc->bg_lock);

	return queued;
}