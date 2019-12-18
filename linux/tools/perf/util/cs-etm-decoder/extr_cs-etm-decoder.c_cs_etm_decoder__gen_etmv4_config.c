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
struct TYPE_4__ {int /*<<< orphan*/  reg_idr8; int /*<<< orphan*/  reg_idr2; int /*<<< orphan*/  reg_idr1; int /*<<< orphan*/  reg_idr0; int /*<<< orphan*/  reg_traceidr; int /*<<< orphan*/  reg_configr; } ;
struct cs_etm_trace_params {TYPE_1__ etmv4; } ;
struct TYPE_5__ {int /*<<< orphan*/  core_prof; int /*<<< orphan*/  arch_ver; scalar_t__ reg_idr13; scalar_t__ reg_idr12; scalar_t__ reg_idr11; scalar_t__ reg_idr10; scalar_t__ reg_idr9; int /*<<< orphan*/  reg_idr8; int /*<<< orphan*/  reg_idr2; int /*<<< orphan*/  reg_idr1; int /*<<< orphan*/  reg_idr0; int /*<<< orphan*/  reg_traceidr; int /*<<< orphan*/  reg_configr; } ;
typedef  TYPE_2__ ocsd_etmv4_cfg ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_V8 ; 
 int /*<<< orphan*/  profile_CortexA ; 

__attribute__((used)) static void cs_etm_decoder__gen_etmv4_config(struct cs_etm_trace_params *params,
					     ocsd_etmv4_cfg *config)
{
	config->reg_configr = params->etmv4.reg_configr;
	config->reg_traceidr = params->etmv4.reg_traceidr;
	config->reg_idr0 = params->etmv4.reg_idr0;
	config->reg_idr1 = params->etmv4.reg_idr1;
	config->reg_idr2 = params->etmv4.reg_idr2;
	config->reg_idr8 = params->etmv4.reg_idr8;
	config->reg_idr9 = 0;
	config->reg_idr10 = 0;
	config->reg_idr11 = 0;
	config->reg_idr12 = 0;
	config->reg_idr13 = 0;
	config->arch_ver = ARCH_V8;
	config->core_prof = profile_CortexA;
}