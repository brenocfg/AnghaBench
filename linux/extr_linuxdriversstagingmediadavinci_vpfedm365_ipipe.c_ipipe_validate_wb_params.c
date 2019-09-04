#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ integer; scalar_t__ decimal; } ;
struct TYPE_7__ {scalar_t__ integer; scalar_t__ decimal; } ;
struct TYPE_6__ {scalar_t__ integer; scalar_t__ decimal; } ;
struct TYPE_5__ {scalar_t__ integer; scalar_t__ decimal; } ;
struct vpfe_ipipe_wb {scalar_t__ ofst_r; scalar_t__ ofst_gr; scalar_t__ ofst_gb; scalar_t__ ofst_b; TYPE_4__ gain_b; TYPE_3__ gain_gb; TYPE_2__ gain_gr; TYPE_1__ gain_r; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WB_GAIN_DECI_MASK ; 
 scalar_t__ WB_GAIN_INT_MASK ; 
 scalar_t__ WB_OFFSET_MASK ; 

__attribute__((used)) static int ipipe_validate_wb_params(struct vpfe_ipipe_wb *wbal)
{
	if (wbal->ofst_r > WB_OFFSET_MASK ||
	    wbal->ofst_gr > WB_OFFSET_MASK ||
	    wbal->ofst_gb > WB_OFFSET_MASK ||
	    wbal->ofst_b > WB_OFFSET_MASK ||
	    wbal->gain_r.integer > WB_GAIN_INT_MASK ||
	    wbal->gain_r.decimal > WB_GAIN_DECI_MASK ||
	    wbal->gain_gr.integer > WB_GAIN_INT_MASK ||
	    wbal->gain_gr.decimal > WB_GAIN_DECI_MASK ||
	    wbal->gain_gb.integer > WB_GAIN_INT_MASK ||
	    wbal->gain_gb.decimal > WB_GAIN_DECI_MASK ||
	    wbal->gain_b.integer > WB_GAIN_INT_MASK ||
	    wbal->gain_b.decimal > WB_GAIN_DECI_MASK)
		return -EINVAL;

	return 0;
}