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
struct ar9170 {int /*<<< orphan*/  tx_anch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_IDLE ; 
 int /*<<< orphan*/  CARL9170_STOPPED ; 
 int /*<<< orphan*/  carl9170_set_state_when (struct ar9170*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unpoison_anchored_urbs (int /*<<< orphan*/ *) ; 

int carl9170_usb_open(struct ar9170 *ar)
{
	usb_unpoison_anchored_urbs(&ar->tx_anch);

	carl9170_set_state_when(ar, CARL9170_STOPPED, CARL9170_IDLE);
	return 0;
}