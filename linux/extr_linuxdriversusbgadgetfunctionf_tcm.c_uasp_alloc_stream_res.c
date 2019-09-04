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
struct uas_stream {int /*<<< orphan*/ * req_out; int /*<<< orphan*/ * req_status; void* req_in; } ;
struct f_uas {int /*<<< orphan*/  ep_out; int /*<<< orphan*/  ep_status; int /*<<< orphan*/  ep_in; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* usb_ep_alloc_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_free_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uasp_alloc_stream_res(struct f_uas *fu, struct uas_stream *stream)
{
	stream->req_in = usb_ep_alloc_request(fu->ep_in, GFP_KERNEL);
	if (!stream->req_in)
		goto out;

	stream->req_out = usb_ep_alloc_request(fu->ep_out, GFP_KERNEL);
	if (!stream->req_out)
		goto err_out;

	stream->req_status = usb_ep_alloc_request(fu->ep_status, GFP_KERNEL);
	if (!stream->req_status)
		goto err_sts;

	return 0;
err_sts:
	usb_ep_free_request(fu->ep_status, stream->req_status);
	stream->req_status = NULL;
err_out:
	usb_ep_free_request(fu->ep_out, stream->req_out);
	stream->req_out = NULL;
out:
	return -ENOMEM;
}