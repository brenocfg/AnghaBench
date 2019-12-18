#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  reg_trc_id; int /*<<< orphan*/  reg_ccer; int /*<<< orphan*/  reg_ctrl; int /*<<< orphan*/  reg_idr; } ;
struct cs_etm_trace_params {TYPE_1__ etmv3; } ;
struct TYPE_5__ {int /*<<< orphan*/  core_prof; int /*<<< orphan*/  arch_ver; int /*<<< orphan*/  reg_trc_id; int /*<<< orphan*/  reg_ccer; int /*<<< orphan*/  reg_ctrl; int /*<<< orphan*/  reg_idr; } ;
typedef  TYPE_2__ ocsd_etmv3_cfg ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_V7 ; 
 int /*<<< orphan*/  profile_CortexA ; 

__attribute__((used)) static int cs_etm_decoder__gen_etmv3_config(struct cs_etm_trace_params *params,
					    ocsd_etmv3_cfg *config)
{
	config->reg_idr = params->etmv3.reg_idr;
	config->reg_ctrl = params->etmv3.reg_ctrl;
	config->reg_ccer = params->etmv3.reg_ccer;
	config->reg_trc_id = params->etmv3.reg_trc_id;
	config->arch_ver = ARCH_V7;
	config->core_prof = profile_CortexA;

	return 0;
}