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
struct ieee802154_hw {struct atusb* priv; } ;
struct atusb {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  SR_MAX_FRAME_RETRIES ; 
 int atusb_write_subreg (struct atusb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atusb_set_frame_retries(struct ieee802154_hw *hw, s8 retries)
{
	struct atusb *atusb = hw->priv;

	return atusb_write_subreg(atusb, SR_MAX_FRAME_RETRIES, retries);
}