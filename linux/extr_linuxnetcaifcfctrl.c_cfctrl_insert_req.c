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
struct cfctrl_request_info {int /*<<< orphan*/  list; int /*<<< orphan*/  sequence_no; } ;
struct cfctrl {int /*<<< orphan*/  info_list_lock; int /*<<< orphan*/  list; int /*<<< orphan*/  req_seq_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cfctrl_insert_req(struct cfctrl *ctrl,
			      struct cfctrl_request_info *req)
{
	spin_lock_bh(&ctrl->info_list_lock);
	atomic_inc(&ctrl->req_seq_no);
	req->sequence_no = atomic_read(&ctrl->req_seq_no);
	list_add_tail(&req->list, &ctrl->list);
	spin_unlock_bh(&ctrl->info_list_lock);
}