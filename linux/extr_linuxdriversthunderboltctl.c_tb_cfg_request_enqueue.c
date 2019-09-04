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
struct tb_ctl {int /*<<< orphan*/  request_queue_lock; int /*<<< orphan*/  request_queue; int /*<<< orphan*/  running; } ;
struct tb_cfg_request {int /*<<< orphan*/  flags; int /*<<< orphan*/  list; struct tb_ctl* ctl; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int /*<<< orphan*/  TB_CFG_REQUEST_ACTIVE ; 
 int /*<<< orphan*/  WARN_ON (struct tb_ctl*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tb_ctl* test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tb_cfg_request_enqueue(struct tb_ctl *ctl,
				  struct tb_cfg_request *req)
{
	WARN_ON(test_bit(TB_CFG_REQUEST_ACTIVE, &req->flags));
	WARN_ON(req->ctl);

	mutex_lock(&ctl->request_queue_lock);
	if (!ctl->running) {
		mutex_unlock(&ctl->request_queue_lock);
		return -ENOTCONN;
	}
	req->ctl = ctl;
	list_add_tail(&req->list, &ctl->request_queue);
	set_bit(TB_CFG_REQUEST_ACTIVE, &req->flags);
	mutex_unlock(&ctl->request_queue_lock);
	return 0;
}