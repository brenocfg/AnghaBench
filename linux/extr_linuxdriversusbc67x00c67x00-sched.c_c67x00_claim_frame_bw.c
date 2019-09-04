#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct urb {int /*<<< orphan*/  pipe; struct c67x00_urb_priv* hcpriv; } ;
struct c67x00_urb_priv {TYPE_2__* ep_data; } ;
struct c67x00_hcd {scalar_t__ bandwidth_allocated; scalar_t__ max_frame_bw; scalar_t__ next_td_addr; scalar_t__ td_base_addr; scalar_t__ next_buf_addr; scalar_t__ buf_base_addr; scalar_t__ periodic_bw_allocated; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {scalar_t__ speed; } ;

/* Variables and functions */
 scalar_t__ CY_TD_SIZE ; 
 int EMSGSIZE ; 
 scalar_t__ MAX_PERIODIC_BW (scalar_t__) ; 
 scalar_t__ SIE_TD_BUF_SIZE ; 
 scalar_t__ SIE_TD_SIZE ; 
 scalar_t__ USB_SPEED_LOW ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipeisoc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int c67x00_claim_frame_bw(struct c67x00_hcd *c67x00, struct urb *urb,
				 int len, int periodic)
{
	struct c67x00_urb_priv *urbp = urb->hcpriv;
	int bit_time;

	/* According to the C67x00 BIOS user manual, page 3-18,19, the
	 * following calculations provide the full speed bit times for
	 * a transaction.
	 *
	 * FS(in)	= 112.5 +  9.36*BC + HOST_DELAY
	 * FS(in,iso)	=  90.5 +  9.36*BC + HOST_DELAY
	 * FS(out)	= 112.5 +  9.36*BC + HOST_DELAY
	 * FS(out,iso)	=  78.4 +  9.36*BC + HOST_DELAY
	 * LS(in)	= 802.4 + 75.78*BC + HOST_DELAY
	 * LS(out)	= 802.6 + 74.67*BC + HOST_DELAY
	 *
	 * HOST_DELAY == 106 for the c67200 and c67300.
	 */

	/* make calculations in 1/100 bit times to maintain resolution */
	if (urbp->ep_data->dev->speed == USB_SPEED_LOW) {
		/* Low speed pipe */
		if (usb_pipein(urb->pipe))
			bit_time = 80240 + 7578*len;
		else
			bit_time = 80260 + 7467*len;
	} else {
		/* FS pipes */
		if (usb_pipeisoc(urb->pipe))
			bit_time = usb_pipein(urb->pipe) ? 9050 : 7840;
		else
			bit_time = 11250;
		bit_time += 936*len;
	}

	/* Scale back down to integer bit times.  Use a host delay of 106.
	 * (this is the only place it is used) */
	bit_time = ((bit_time+50) / 100) + 106;

	if (unlikely(bit_time + c67x00->bandwidth_allocated >=
		     c67x00->max_frame_bw))
		return -EMSGSIZE;

	if (unlikely(c67x00->next_td_addr + CY_TD_SIZE >=
		     c67x00->td_base_addr + SIE_TD_SIZE))
		return -EMSGSIZE;

	if (unlikely(c67x00->next_buf_addr + len >=
		     c67x00->buf_base_addr + SIE_TD_BUF_SIZE))
		return -EMSGSIZE;

	if (periodic) {
		if (unlikely(bit_time + c67x00->periodic_bw_allocated >=
			     MAX_PERIODIC_BW(c67x00->max_frame_bw)))
			return -EMSGSIZE;
		c67x00->periodic_bw_allocated += bit_time;
	}

	c67x00->bandwidth_allocated += bit_time;
	return 0;
}