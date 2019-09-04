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
struct tb_ctl {int dummy; } ;
struct tb_cfg_request {void (* callback ) (void*) ;int /*<<< orphan*/  work; int /*<<< orphan*/  response; int /*<<< orphan*/  request_type; int /*<<< orphan*/  request_size; int /*<<< orphan*/  request; int /*<<< orphan*/  list; void* callback_data; scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_cfg_request_dequeue (struct tb_cfg_request*) ; 
 int tb_cfg_request_enqueue (struct tb_ctl*,struct tb_cfg_request*) ; 
 int /*<<< orphan*/  tb_cfg_request_get (struct tb_cfg_request*) ; 
 int /*<<< orphan*/  tb_cfg_request_put (struct tb_cfg_request*) ; 
 int /*<<< orphan*/  tb_cfg_request_work ; 
 int tb_ctl_tx (struct tb_ctl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tb_cfg_request(struct tb_ctl *ctl, struct tb_cfg_request *req,
		   void (*callback)(void *), void *callback_data)
{
	int ret;

	req->flags = 0;
	req->callback = callback;
	req->callback_data = callback_data;
	INIT_WORK(&req->work, tb_cfg_request_work);
	INIT_LIST_HEAD(&req->list);

	tb_cfg_request_get(req);
	ret = tb_cfg_request_enqueue(ctl, req);
	if (ret)
		goto err_put;

	ret = tb_ctl_tx(ctl, req->request, req->request_size,
			req->request_type);
	if (ret)
		goto err_dequeue;

	if (!req->response)
		schedule_work(&req->work);

	return 0;

err_dequeue:
	tb_cfg_request_dequeue(req);
err_put:
	tb_cfg_request_put(req);

	return ret;
}