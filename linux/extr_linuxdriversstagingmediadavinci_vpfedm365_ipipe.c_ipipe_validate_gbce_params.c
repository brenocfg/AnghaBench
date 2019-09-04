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
typedef  scalar_t__ u32 ;
struct vpfe_ipipe_gbce {scalar_t__ type; scalar_t__* table; int /*<<< orphan*/  en; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GBCE_GAIN_VAL_MASK ; 
 scalar_t__ GBCE_Y_VAL_MASK ; 
 scalar_t__ VPFE_IPIPE_GBCE_GAIN_TBL ; 
 int VPFE_IPIPE_MAX_SIZE_GBCE_LUT ; 

__attribute__((used)) static int ipipe_validate_gbce_params(struct vpfe_ipipe_gbce *gbce)
{
	u32 max = GBCE_Y_VAL_MASK;
	int i;

	if (!gbce->en)
		return 0;

	if (gbce->type == VPFE_IPIPE_GBCE_GAIN_TBL)
		max = GBCE_GAIN_VAL_MASK;

	for (i = 0; i < VPFE_IPIPE_MAX_SIZE_GBCE_LUT; i++)
		if (gbce->table[i] > max)
			return -EINVAL;

	return 0;
}