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
struct vpfe_ipipe_3d_lut {int /*<<< orphan*/  table; int /*<<< orphan*/  en; } ;
struct TYPE_2__ {struct vpfe_ipipe_3d_lut lut; } ;
struct vpfe_ipipe_device {TYPE_1__ config; } ;
struct vpfe_ipipe_3d_lut_entry {int dummy; } ;

/* Variables and functions */
 int VPFE_IPIPE_MAX_SIZE_3D_LUT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ipipe_get_3d_lut_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_3d_lut *lut_param = param;
	struct vpfe_ipipe_3d_lut *lut = &ipipe->config.lut;

	lut_param->en = lut->en;

	memcpy(lut_param->table, &lut->table,
	       (VPFE_IPIPE_MAX_SIZE_3D_LUT *
	       sizeof(struct vpfe_ipipe_3d_lut_entry)));

	return 0;
}