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
struct ath6kl_usb {TYPE_1__* pipes; } ;
struct TYPE_2__ {int urb_cnt_thresh; } ;

/* Variables and functions */
 size_t ATH6KL_USB_PIPE_RX_DATA ; 
 int /*<<< orphan*/  ATH6KL_USB_RX_BUFFER_SIZE ; 
 int /*<<< orphan*/  ath6kl_usb_post_recv_transfers (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath6kl_usb_start_recv_pipes(struct ath6kl_usb *ar_usb)
{
	/*
	 * note: control pipe is no longer used
	 * ar_usb->pipes[ATH6KL_USB_PIPE_RX_CTRL].urb_cnt_thresh =
	 *      ar_usb->pipes[ATH6KL_USB_PIPE_RX_CTRL].urb_alloc/2;
	 * ath6kl_usb_post_recv_transfers(&ar_usb->
	 *		pipes[ATH6KL_USB_PIPE_RX_CTRL],
	 *		ATH6KL_USB_RX_BUFFER_SIZE);
	 */

	ar_usb->pipes[ATH6KL_USB_PIPE_RX_DATA].urb_cnt_thresh = 1;

	ath6kl_usb_post_recv_transfers(&ar_usb->pipes[ATH6KL_USB_PIPE_RX_DATA],
				       ATH6KL_USB_RX_BUFFER_SIZE);
}