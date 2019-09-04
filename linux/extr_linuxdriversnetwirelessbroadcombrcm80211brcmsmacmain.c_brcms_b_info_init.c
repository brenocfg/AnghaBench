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
struct brcms_hardware {int shortslot; int /*<<< orphan*/  chanspec; int /*<<< orphan*/  LRL; int /*<<< orphan*/  SRL; int /*<<< orphan*/  LFBL; int /*<<< orphan*/  SFBL; struct brcms_c_info* wlc; } ;
struct brcms_c_info {int /*<<< orphan*/  defmacintmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_MACINTMASK ; 
 int /*<<< orphan*/  RETRY_LONG_DEF ; 
 int /*<<< orphan*/  RETRY_LONG_FB ; 
 int /*<<< orphan*/  RETRY_SHORT_DEF ; 
 int /*<<< orphan*/  RETRY_SHORT_FB ; 
 int /*<<< orphan*/  ch20mhz_chspec (int) ; 

__attribute__((used)) static void brcms_b_info_init(struct brcms_hardware *wlc_hw)
{
	struct brcms_c_info *wlc = wlc_hw->wlc;

	/* set default sw macintmask value */
	wlc->defmacintmask = DEF_MACINTMASK;

	/* various 802.11g modes */
	wlc_hw->shortslot = false;

	wlc_hw->SFBL = RETRY_SHORT_FB;
	wlc_hw->LFBL = RETRY_LONG_FB;

	/* default mac retry limits */
	wlc_hw->SRL = RETRY_SHORT_DEF;
	wlc_hw->LRL = RETRY_LONG_DEF;
	wlc_hw->chanspec = ch20mhz_chspec(1);
}