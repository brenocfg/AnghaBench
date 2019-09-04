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
struct vpfe_device {struct vpfe_isif_device vpfe_isif; } ;

/* Variables and functions */
 int /*<<< orphan*/  CADL ; 
 int /*<<< orphan*/  CADU ; 
 unsigned long ISIF_CADL_BITS ; 
 unsigned long ISIF_CADU_BITS ; 
 int /*<<< orphan*/  isif_write (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isif_video_queue(struct vpfe_device *vpfe_dev, unsigned long addr)
{
	struct vpfe_isif_device *isif = &vpfe_dev->vpfe_isif;

	isif_write(isif->isif_cfg.base_addr, (addr >> 21) &
		ISIF_CADU_BITS, CADU);
	isif_write(isif->isif_cfg.base_addr, (addr >> 5) &
		ISIF_CADL_BITS, CADL);

	return 0;
}