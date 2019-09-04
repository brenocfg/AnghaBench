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
struct vpfe_ipipe_lutdpc {int en; int repl_white; int dpc_size; TYPE_1__* table; } ;
struct TYPE_2__ {scalar_t__ horz_pos; scalar_t__ vert_pos; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ LUT_DPC_H_POS_MASK ; 
 int LUT_DPC_MAX_SIZE ; 
 scalar_t__ LUT_DPC_V_POS_MASK ; 

__attribute__((used)) static int ipipe_validate_lutdpc_params(struct vpfe_ipipe_lutdpc *lutdpc)
{
	int i;

	if (lutdpc->en > 1 || lutdpc->repl_white > 1 ||
	    lutdpc->dpc_size > LUT_DPC_MAX_SIZE)
		return -EINVAL;

	if (lutdpc->en)
		return -EINVAL;

	for (i = 0; i < lutdpc->dpc_size; i++)
		if (lutdpc->table[i].horz_pos > LUT_DPC_H_POS_MASK ||
		   lutdpc->table[i].vert_pos > LUT_DPC_V_POS_MASK)
			return -EINVAL;

	return 0;
}