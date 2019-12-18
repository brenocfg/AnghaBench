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
typedef  int /*<<< orphan*/  plain_desc ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;
typedef  int /*<<< orphan*/  define_name ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
#define  BPF_PROG_TYPE_SCHED_CLS 129 
#define  BPF_PROG_TYPE_XDP 128 
 int bpf_probe_prog_type (int,scalar_t__) ; 
 int /*<<< orphan*/  p_info (char*) ; 
 int /*<<< orphan*/  print_bool_feature (char*,char*,char*,int,char const*) ; 
 char** prog_type_name ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,...) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  uppercase (char*,int) ; 

__attribute__((used)) static void
probe_prog_type(enum bpf_prog_type prog_type, bool *supported_types,
		const char *define_prefix, __u32 ifindex)
{
	char feat_name[128], plain_desc[128], define_name[128];
	const char *plain_comment = "eBPF program_type ";
	size_t maxlen;
	bool res;

	if (ifindex)
		/* Only test offload-able program types */
		switch (prog_type) {
		case BPF_PROG_TYPE_SCHED_CLS:
		case BPF_PROG_TYPE_XDP:
			break;
		default:
			return;
		}

	res = bpf_probe_prog_type(prog_type, ifindex);

	supported_types[prog_type] |= res;

	maxlen = sizeof(plain_desc) - strlen(plain_comment) - 1;
	if (strlen(prog_type_name[prog_type]) > maxlen) {
		p_info("program type name too long");
		return;
	}

	sprintf(feat_name, "have_%s_prog_type", prog_type_name[prog_type]);
	sprintf(define_name, "%s_prog_type", prog_type_name[prog_type]);
	uppercase(define_name, sizeof(define_name));
	sprintf(plain_desc, "%s%s", plain_comment, prog_type_name[prog_type]);
	print_bool_feature(feat_name, plain_desc, define_name, res,
			   define_prefix);
}