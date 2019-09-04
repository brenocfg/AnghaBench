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
struct urb {unsigned int stream_id; int /*<<< orphan*/  pipe; } ;
struct dummy_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dummy_dev (struct dummy_hcd*) ; 
 int dummy_ep_stream_en (struct dummy_hcd*,struct urb*) ; 
 unsigned int get_max_streams_for_pipe (struct dummy_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipeendpoint (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dummy_validate_stream(struct dummy_hcd *dum_hcd, struct urb *urb)
{
	unsigned int max_streams;
	int enabled;

	enabled = dummy_ep_stream_en(dum_hcd, urb);
	if (!urb->stream_id) {
		if (enabled)
			return -EINVAL;
		return 0;
	}
	if (!enabled)
		return -EINVAL;

	max_streams = get_max_streams_for_pipe(dum_hcd,
			usb_pipeendpoint(urb->pipe));
	if (urb->stream_id > max_streams) {
		dev_err(dummy_dev(dum_hcd), "Stream id %d is out of range.\n",
				urb->stream_id);
		BUG();
		return -EINVAL;
	}
	return 0;
}