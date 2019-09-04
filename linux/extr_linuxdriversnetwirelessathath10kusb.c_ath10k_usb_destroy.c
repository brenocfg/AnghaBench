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
struct ath10k_usb {int /*<<< orphan*/  diag_resp_buffer; int /*<<< orphan*/  diag_cmd_buffer; int /*<<< orphan*/  interface; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_usb_cleanup_pipe_resources (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_usb_flush_all (struct ath10k*) ; 
 struct ath10k_usb* ath10k_usb_priv (struct ath10k*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_usb_destroy(struct ath10k *ar)
{
	struct ath10k_usb *ar_usb = ath10k_usb_priv(ar);

	ath10k_usb_flush_all(ar);
	ath10k_usb_cleanup_pipe_resources(ar);
	usb_set_intfdata(ar_usb->interface, NULL);

	kfree(ar_usb->diag_cmd_buffer);
	kfree(ar_usb->diag_resp_buffer);
}