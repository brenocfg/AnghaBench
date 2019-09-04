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
struct ufs_vreg {int /*<<< orphan*/  max_uA; scalar_t__ unused; } ;
struct ufs_hba {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ufshcd_config_vreg_load (int /*<<< orphan*/ ,struct ufs_vreg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ufshcd_config_vreg_hpm(struct ufs_hba *hba,
					 struct ufs_vreg *vreg)
{
	if (!vreg)
		return 0;
	else if (vreg->unused)
		return 0;
	else
		return ufshcd_config_vreg_load(hba->dev, vreg, vreg->max_uA);
}