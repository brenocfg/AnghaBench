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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  base_addr; } ;
struct vpfe_isif_device {TYPE_1__ isif_cfg; } ;
struct vpfe_device {struct vpfe_isif_device vpfe_isif; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int DM365_ISIF_MDFS_MASK ; 
 int DM365_ISIF_MDFS_OFFSET ; 
 int /*<<< orphan*/  MODESET ; 
 int isif_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum v4l2_field vpfe_isif_get_fid(struct vpfe_device *vpfe_dev)
{
	struct vpfe_isif_device *isif = &vpfe_dev->vpfe_isif;
	u32 field_status;

	field_status = isif_read(isif->isif_cfg.base_addr, MODESET);
	return (field_status >> DM365_ISIF_MDFS_OFFSET) &
		DM365_ISIF_MDFS_MASK;
}