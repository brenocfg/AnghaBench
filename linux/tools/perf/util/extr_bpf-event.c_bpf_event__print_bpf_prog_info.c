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
typedef  int u32 ;
struct perf_env {int dummy; } ;
struct btf_node {int /*<<< orphan*/  data_size; scalar_t__ data; } ;
struct btf {int dummy; } ;
struct bpf_prog_info {int nr_jited_ksyms; int nr_prog_tags; int nr_jited_func_lens; int id; scalar_t__ btf_id; scalar_t__ jited_ksyms; scalar_t__ jited_func_lens; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int KSYM_NAME_LEN ; 
 struct btf* btf__new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,...) ; 
 struct btf_node* perf_env__find_btf (struct perf_env*,scalar_t__) ; 
 int /*<<< orphan*/  synthesize_bpf_prog_name (char*,int,struct bpf_prog_info*,struct btf*,int) ; 

void bpf_event__print_bpf_prog_info(struct bpf_prog_info *info,
				    struct perf_env *env,
				    FILE *fp)
{
	__u32 *prog_lens = (__u32 *)(uintptr_t)(info->jited_func_lens);
	__u64 *prog_addrs = (__u64 *)(uintptr_t)(info->jited_ksyms);
	char name[KSYM_NAME_LEN];
	struct btf *btf = NULL;
	u32 sub_prog_cnt, i;

	sub_prog_cnt = info->nr_jited_ksyms;
	if (sub_prog_cnt != info->nr_prog_tags ||
	    sub_prog_cnt != info->nr_jited_func_lens)
		return;

	if (info->btf_id) {
		struct btf_node *node;

		node = perf_env__find_btf(env, info->btf_id);
		if (node)
			btf = btf__new((__u8 *)(node->data),
				       node->data_size);
	}

	if (sub_prog_cnt == 1) {
		synthesize_bpf_prog_name(name, KSYM_NAME_LEN, info, btf, 0);
		fprintf(fp, "# bpf_prog_info %u: %s addr 0x%llx size %u\n",
			info->id, name, prog_addrs[0], prog_lens[0]);
		return;
	}

	fprintf(fp, "# bpf_prog_info %u:\n", info->id);
	for (i = 0; i < sub_prog_cnt; i++) {
		synthesize_bpf_prog_name(name, KSYM_NAME_LEN, info, btf, i);

		fprintf(fp, "# \tsub_prog %u: %s addr 0x%llx size %u\n",
			i, name, prog_addrs[i], prog_lens[i]);
	}
}