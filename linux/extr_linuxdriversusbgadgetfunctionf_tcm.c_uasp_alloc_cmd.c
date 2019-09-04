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
struct TYPE_6__ {TYPE_3__* req; scalar_t__ buf; } ;
struct f_uas {TYPE_1__ cmd; TYPE_2__* ep_cmd; } ;
struct TYPE_8__ {struct f_uas* context; int /*<<< orphan*/  length; scalar_t__ buf; int /*<<< orphan*/  complete; } ;
struct TYPE_7__ {int /*<<< orphan*/  maxpacket; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasp_cmd_complete ; 
 TYPE_3__* usb_ep_alloc_request (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_free_request (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static int uasp_alloc_cmd(struct f_uas *fu)
{
	fu->cmd.req = usb_ep_alloc_request(fu->ep_cmd, GFP_KERNEL);
	if (!fu->cmd.req)
		goto err;

	fu->cmd.buf = kmalloc(fu->ep_cmd->maxpacket, GFP_KERNEL);
	if (!fu->cmd.buf)
		goto err_buf;

	fu->cmd.req->complete = uasp_cmd_complete;
	fu->cmd.req->buf = fu->cmd.buf;
	fu->cmd.req->length = fu->ep_cmd->maxpacket;
	fu->cmd.req->context = fu;
	return 0;

err_buf:
	usb_ep_free_request(fu->ep_cmd, fu->cmd.req);
err:
	return -ENOMEM;
}