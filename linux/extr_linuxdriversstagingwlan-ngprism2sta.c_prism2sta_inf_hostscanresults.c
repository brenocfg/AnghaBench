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
struct wlandevice {struct hfa384x* priv; } ;
struct hfa384x_inf_frame {int framelen; } ;
struct hfa384x {int scanflag; int /*<<< orphan*/  cmdq; int /*<<< orphan*/  scanresults; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemdup (struct hfa384x_inf_frame*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prism2sta_inf_hostscanresults(struct wlandevice *wlandev,
					  struct hfa384x_inf_frame *inf)
{
	struct hfa384x *hw = wlandev->priv;
	int nbss;

	nbss = (inf->framelen - 3) / 32;
	pr_debug("Received %d hostscan results\n", nbss);

	if (nbss > 32)
		nbss = 32;

	kfree(hw->scanresults);

	hw->scanresults = kmemdup(inf, sizeof(*inf), GFP_ATOMIC);

	if (nbss == 0)
		nbss = -1;

	/* Notify/wake the sleeping caller. */
	hw->scanflag = nbss;
	wake_up_interruptible(&hw->cmdq);
}