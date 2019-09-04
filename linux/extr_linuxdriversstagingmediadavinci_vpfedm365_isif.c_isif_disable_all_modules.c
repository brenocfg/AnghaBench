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
 int /*<<< orphan*/  CLAMPCFG ; 
 int /*<<< orphan*/  CSCCTL ; 
 int /*<<< orphan*/  DFCCTL ; 
 int /*<<< orphan*/  LINCFG0 ; 
 int /*<<< orphan*/  isif_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isif_disable_all_modules(struct vpfe_isif_device *isif)
{
	/* disable BC */
	isif_write(isif->isif_cfg.base_addr, 0, CLAMPCFG);
	/* disable vdfc */
	isif_write(isif->isif_cfg.base_addr, 0, DFCCTL);
	/* disable CSC */
	isif_write(isif->isif_cfg.base_addr, 0, CSCCTL);
	/* disable linearization */
	isif_write(isif->isif_cfg.base_addr, 0, LINCFG0);
}