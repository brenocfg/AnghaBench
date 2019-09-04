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
struct pcf50633_mbc {int usb_online; } ;
struct pcf50633 {int /*<<< orphan*/  mbc_pdev; } ;

/* Variables and functions */
 struct pcf50633_mbc* platform_get_drvdata (int /*<<< orphan*/ ) ; 

int pcf50633_mbc_get_usb_online_status(struct pcf50633 *pcf)
{
	struct pcf50633_mbc *mbc  = platform_get_drvdata(pcf->mbc_pdev);

	if (!mbc)
		return 0;

	return mbc->usb_online;
}