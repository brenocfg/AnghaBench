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
struct uvc_video {scalar_t__ req_size; int /*<<< orphan*/  req_free; int /*<<< orphan*/ ** req_buffer; int /*<<< orphan*/ ** req; int /*<<< orphan*/  ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int UVC_NUM_REQUESTS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_ep_free_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
uvc_video_free_requests(struct uvc_video *video)
{
	unsigned int i;

	for (i = 0; i < UVC_NUM_REQUESTS; ++i) {
		if (video->req[i]) {
			usb_ep_free_request(video->ep, video->req[i]);
			video->req[i] = NULL;
		}

		if (video->req_buffer[i]) {
			kfree(video->req_buffer[i]);
			video->req_buffer[i] = NULL;
		}
	}

	INIT_LIST_HEAD(&video->req_free);
	video->req_size = 0;
	return 0;
}