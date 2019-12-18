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
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char**) ; 
#define  BPF_PROG_TYPE_SCHED_CLS 129 
#define  BPF_PROG_TYPE_XDP 128 
 int bpf_probe_helper (unsigned int,int,int /*<<< orphan*/ ) ; 
 char** helper_name ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_end_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jsonw_start_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char** prog_type_name ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static void
probe_helpers_for_progtype(enum bpf_prog_type prog_type, bool supported_type,
			   const char *define_prefix, __u32 ifindex)
{
	const char *ptype_name = prog_type_name[prog_type];
	char feat_name[128];
	unsigned int id;
	bool res;

	if (ifindex)
		/* Only test helpers for offload-able program types */
		switch (prog_type) {
		case BPF_PROG_TYPE_SCHED_CLS:
		case BPF_PROG_TYPE_XDP:
			break;
		default:
			return;
		}

	if (json_output) {
		sprintf(feat_name, "%s_available_helpers", ptype_name);
		jsonw_name(json_wtr, feat_name);
		jsonw_start_array(json_wtr);
	} else if (!define_prefix) {
		printf("eBPF helpers supported for program type %s:",
		       ptype_name);
	}

	for (id = 1; id < ARRAY_SIZE(helper_name); id++) {
		if (!supported_type)
			res = false;
		else
			res = bpf_probe_helper(id, prog_type, ifindex);

		if (json_output) {
			if (res)
				jsonw_string(json_wtr, helper_name[id]);
		} else if (define_prefix) {
			printf("#define %sBPF__PROG_TYPE_%s__HELPER_%s %s\n",
			       define_prefix, ptype_name, helper_name[id],
			       res ? "1" : "0");
		} else {
			if (res)
				printf("\n\t- %s", helper_name[id]);
		}
	}

	if (json_output)
		jsonw_end_array(json_wtr);
	else if (!define_prefix)
		printf("\n");
}