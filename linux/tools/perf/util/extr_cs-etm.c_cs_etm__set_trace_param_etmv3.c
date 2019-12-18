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
typedef  void* u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {void* reg_trc_id; void* reg_ctrl; } ;
struct cs_etm_trace_params {TYPE_1__ etmv3; int /*<<< orphan*/  protocol; } ;
struct cs_etm_auxtrace {void*** metadata; } ;

/* Variables and functions */
 size_t CS_ETM_ETMCR ; 
 size_t CS_ETM_ETMTRACEIDR ; 
 int /*<<< orphan*/  cs_etm__get_v7_protocol_version (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs_etm__set_trace_param_etmv3(struct cs_etm_trace_params *t_params,
					  struct cs_etm_auxtrace *etm, int idx,
					  u32 etmidr)
{
	u64 **metadata = etm->metadata;

	t_params[idx].protocol = cs_etm__get_v7_protocol_version(etmidr);
	t_params[idx].etmv3.reg_ctrl = metadata[idx][CS_ETM_ETMCR];
	t_params[idx].etmv3.reg_trc_id = metadata[idx][CS_ETM_ETMTRACEIDR];
}