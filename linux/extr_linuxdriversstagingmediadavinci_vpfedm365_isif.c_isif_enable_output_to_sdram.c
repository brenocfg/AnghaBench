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
 int /*<<< orphan*/  ISIF_SYNCEN_WEN_MASK ; 
 int ISIF_SYNCEN_WEN_SHIFT ; 
 int /*<<< orphan*/  SYNCEN ; 
 int /*<<< orphan*/  isif_merge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isif_enable_output_to_sdram(struct vpfe_isif_device *isif, int en)
{
	isif_merge(isif->isif_cfg.base_addr, ISIF_SYNCEN_WEN_MASK,
		   en << ISIF_SYNCEN_WEN_SHIFT, SYNCEN);
}