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
struct aac_dev {scalar_t__ msi_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_ENABLE_INTX ; 
 int /*<<< orphan*/  aac_src_access_devreg (struct aac_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

void aac_set_intx_mode(struct aac_dev *dev)
{
	if (dev->msi_enabled) {
		aac_src_access_devreg(dev, AAC_ENABLE_INTX);
		dev->msi_enabled = 0;
		msleep(5000); /* Delay 5 seconds */
	}
}