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
struct ath10k_urb_context {int /*<<< orphan*/  pipe; int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_usb_free_urb_to_pipe (int /*<<< orphan*/ ,struct ath10k_urb_context*) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_usb_cleanup_recv_urb(struct ath10k_urb_context *urb_context)
{
	dev_kfree_skb(urb_context->skb);
	urb_context->skb = NULL;

	ath10k_usb_free_urb_to_pipe(urb_context->pipe, urb_context);
}