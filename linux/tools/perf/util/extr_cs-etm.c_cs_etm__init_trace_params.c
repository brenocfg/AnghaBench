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
typedef  int u64 ;
typedef  int u32 ;
struct cs_etm_trace_params {int dummy; } ;
struct cs_etm_auxtrace {int num_cpu; int** metadata; } ;

/* Variables and functions */
 size_t CS_ETM_ETMIDR ; 
 size_t CS_ETM_MAGIC ; 
 int EINVAL ; 
#define  __perf_cs_etmv3_magic 129 
#define  __perf_cs_etmv4_magic 128 
 int /*<<< orphan*/  cs_etm__set_trace_param_etmv3 (struct cs_etm_trace_params*,struct cs_etm_auxtrace*,int,int) ; 
 int /*<<< orphan*/  cs_etm__set_trace_param_etmv4 (struct cs_etm_trace_params*,struct cs_etm_auxtrace*,int) ; 

__attribute__((used)) static int cs_etm__init_trace_params(struct cs_etm_trace_params *t_params,
				     struct cs_etm_auxtrace *etm)
{
	int i;
	u32 etmidr;
	u64 architecture;

	for (i = 0; i < etm->num_cpu; i++) {
		architecture = etm->metadata[i][CS_ETM_MAGIC];

		switch (architecture) {
		case __perf_cs_etmv3_magic:
			etmidr = etm->metadata[i][CS_ETM_ETMIDR];
			cs_etm__set_trace_param_etmv3(t_params, etm, i, etmidr);
			break;
		case __perf_cs_etmv4_magic:
			cs_etm__set_trace_param_etmv4(t_params, etm, i);
			break;
		default:
			return -EINVAL;
		}
	}

	return 0;
}