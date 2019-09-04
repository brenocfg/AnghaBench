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
struct ath6kl_usb {struct ath6kl_usb* diag_resp_buffer; struct ath6kl_usb* diag_cmd_buffer; int /*<<< orphan*/  interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_usb_cleanup_pipe_resources (struct ath6kl_usb*) ; 
 int /*<<< orphan*/  ath6kl_usb_flush_all (struct ath6kl_usb*) ; 
 int /*<<< orphan*/  kfree (struct ath6kl_usb*) ; 
 int /*<<< orphan*/  usb_set_intfdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath6kl_usb_destroy(struct ath6kl_usb *ar_usb)
{
	ath6kl_usb_flush_all(ar_usb);

	ath6kl_usb_cleanup_pipe_resources(ar_usb);

	usb_set_intfdata(ar_usb->interface, NULL);

	kfree(ar_usb->diag_cmd_buffer);
	kfree(ar_usb->diag_resp_buffer);

	kfree(ar_usb);
}