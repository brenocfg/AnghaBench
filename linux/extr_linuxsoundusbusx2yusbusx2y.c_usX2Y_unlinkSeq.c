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
struct snd_usX2Y_AsyncSeq {int /*<<< orphan*/  buffer; int /*<<< orphan*/ ** urb; } ;

/* Variables and functions */
 int URBS_AsyncSeq ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usX2Y_unlinkSeq(struct snd_usX2Y_AsyncSeq *S)
{
	int	i;
	for (i = 0; i < URBS_AsyncSeq; ++i) {
		usb_kill_urb(S->urb[i]);
		usb_free_urb(S->urb[i]);
		S->urb[i] = NULL;
	}
	kfree(S->buffer);
}