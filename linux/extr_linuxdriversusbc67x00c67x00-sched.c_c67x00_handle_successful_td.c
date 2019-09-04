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
struct urb {int interval; int /*<<< orphan*/  actual_length; int /*<<< orphan*/  transfer_buffer_length; } ;
struct c67x00_td {int /*<<< orphan*/  privdata; int /*<<< orphan*/  pipe; struct urb* urb; } ;
struct c67x00_hcd {int dummy; } ;

/* Variables and functions */
#define  DATA_STAGE 133 
#define  PIPE_BULK 132 
#define  PIPE_CONTROL 131 
#define  PIPE_INTERRUPT 130 
#define  SETUP_STAGE 129 
#define  STATUS_STAGE 128 
 int /*<<< orphan*/  c67x00_clear_pipe (struct c67x00_hcd*,struct c67x00_td*) ; 
 int /*<<< orphan*/  c67x00_end_of_data (struct c67x00_td*) ; 
 int /*<<< orphan*/  c67x00_giveback_urb (struct c67x00_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 scalar_t__ td_actual_bytes (struct c67x00_td*) ; 
 int /*<<< orphan*/  unlikely (int /*<<< orphan*/ ) ; 
 int usb_pipetype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void c67x00_handle_successful_td(struct c67x00_hcd *c67x00,
					struct c67x00_td *td)
{
	struct urb *urb = td->urb;

	if (!urb)
		return;

	urb->actual_length += td_actual_bytes(td);

	switch (usb_pipetype(td->pipe)) {
		/* isochronous tds are handled separately */
	case PIPE_CONTROL:
		switch (td->privdata) {
		case SETUP_STAGE:
			urb->interval =
			    urb->transfer_buffer_length ?
			    DATA_STAGE : STATUS_STAGE;
			/* Don't count setup_packet with normal data: */
			urb->actual_length = 0;
			break;

		case DATA_STAGE:
			if (c67x00_end_of_data(td)) {
				urb->interval = STATUS_STAGE;
				c67x00_clear_pipe(c67x00, td);
			}
			break;

		case STATUS_STAGE:
			urb->interval = 0;
			c67x00_giveback_urb(c67x00, urb, 0);
			break;
		}
		break;

	case PIPE_INTERRUPT:
	case PIPE_BULK:
		if (unlikely(c67x00_end_of_data(td))) {
			c67x00_clear_pipe(c67x00, td);
			c67x00_giveback_urb(c67x00, urb, 0);
		}
		break;
	}
}