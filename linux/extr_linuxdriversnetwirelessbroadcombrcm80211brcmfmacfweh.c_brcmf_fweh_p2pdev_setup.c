#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct brcmf_if {TYPE_2__* drvr; } ;
struct TYPE_3__ {int p2pdev_setup_ongoing; } ;
struct TYPE_4__ {TYPE_1__ fweh; } ;

/* Variables and functions */

void brcmf_fweh_p2pdev_setup(struct brcmf_if *ifp, bool ongoing)
{
	ifp->drvr->fweh.p2pdev_setup_ongoing = ongoing;
}