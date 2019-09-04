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
struct vpfe_ipipe_3d_lut {TYPE_1__* table; int /*<<< orphan*/  en; } ;
struct TYPE_2__ {scalar_t__ r; scalar_t__ g; scalar_t__ b; } ;

/* Variables and functions */
 scalar_t__ D3_LUT_ENTRY_MASK ; 
 int EINVAL ; 
 int VPFE_IPIPE_MAX_SIZE_3D_LUT ; 

__attribute__((used)) static int ipipe_validate_3d_lut_params(struct vpfe_ipipe_3d_lut *lut)
{
	int i;

	if (!lut->en)
		return 0;

	for (i = 0; i < VPFE_IPIPE_MAX_SIZE_3D_LUT; i++)
		if (lut->table[i].r > D3_LUT_ENTRY_MASK ||
		    lut->table[i].g > D3_LUT_ENTRY_MASK ||
		    lut->table[i].b > D3_LUT_ENTRY_MASK)
			return -EINVAL;

	return 0;
}