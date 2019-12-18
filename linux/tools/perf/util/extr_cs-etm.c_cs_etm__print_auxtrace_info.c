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
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int CS_ETMV4_PRIV_MAX ; 
 int CS_ETM_PRIV_MAX ; 
 int CS_HEADER_VERSION_0_MAX ; 
 scalar_t__ __perf_cs_etmv3_magic ; 
 scalar_t__ __perf_cs_etmv4_magic ; 
 char** cs_etm_global_header_fmts ; 
 char** cs_etm_priv_fmts ; 
 char** cs_etmv4_priv_fmts ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void cs_etm__print_auxtrace_info(__u64 *val, int num)
{
	int i, j, cpu = 0;

	for (i = 0; i < CS_HEADER_VERSION_0_MAX; i++)
		fprintf(stdout, cs_etm_global_header_fmts[i], val[i]);

	for (i = CS_HEADER_VERSION_0_MAX; cpu < num; cpu++) {
		if (val[i] == __perf_cs_etmv3_magic)
			for (j = 0; j < CS_ETM_PRIV_MAX; j++, i++)
				fprintf(stdout, cs_etm_priv_fmts[j], val[i]);
		else if (val[i] == __perf_cs_etmv4_magic)
			for (j = 0; j < CS_ETMV4_PRIV_MAX; j++, i++)
				fprintf(stdout, cs_etmv4_priv_fmts[j], val[i]);
		else
			/* failure.. return */
			return;
	}
}