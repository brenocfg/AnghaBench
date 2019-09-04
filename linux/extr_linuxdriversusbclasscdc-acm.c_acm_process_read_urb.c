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
struct urb {int /*<<< orphan*/  actual_length; int /*<<< orphan*/  transfer_buffer; } ;
struct acm {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_insert_flip_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acm_process_read_urb(struct acm *acm, struct urb *urb)
{
	if (!urb->actual_length)
		return;

	tty_insert_flip_string(&acm->port, urb->transfer_buffer,
			urb->actual_length);
	tty_flip_buffer_push(&acm->port);
}