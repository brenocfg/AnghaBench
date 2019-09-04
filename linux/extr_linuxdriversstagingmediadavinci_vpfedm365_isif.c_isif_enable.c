#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  base_addr; } ;
struct vpfe_isif_device {TYPE_1__ isif_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISIF_SYNCEN_VDHDEN_MASK ; 
 int /*<<< orphan*/  SYNCEN ; 
 int /*<<< orphan*/  isif_disable_all_modules (struct vpfe_isif_device*) ; 
 int /*<<< orphan*/  isif_merge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void isif_enable(struct vpfe_isif_device *isif, int en)
{
	if (!en)
		/* Before disable isif, disable all ISIF modules */
		isif_disable_all_modules(isif);

	/*
	 * wait for next VD. Assume lowest scan rate is 12 Hz. So
	 * 100 msec delay is good enough
	 */
	msleep(100);
	isif_merge(isif->isif_cfg.base_addr, ISIF_SYNCEN_VDHDEN_MASK,
		   en, SYNCEN);
}