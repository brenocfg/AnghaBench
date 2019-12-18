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
typedef  int /*<<< orphan*/  u64 ;
struct bpf_prog {int /*<<< orphan*/  jited_len; scalar_t__ bpf_func; TYPE_1__* aux; } ;
typedef  enum perf_bpf_event_type { ____Placeholder_perf_bpf_event_type } perf_bpf_event_type ;
struct TYPE_2__ {int func_cnt; struct bpf_prog** func; } ;

/* Variables and functions */
 int KSYM_NAME_LEN ; 
 int PERF_BPF_EVENT_PROG_UNLOAD ; 
 int /*<<< orphan*/  PERF_RECORD_KSYMBOL_TYPE_BPF ; 
 int /*<<< orphan*/  bpf_get_prog_name (struct bpf_prog*,char*) ; 
 int /*<<< orphan*/  perf_event_ksymbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static void perf_event_bpf_emit_ksymbols(struct bpf_prog *prog,
					 enum perf_bpf_event_type type)
{
	bool unregister = type == PERF_BPF_EVENT_PROG_UNLOAD;
	char sym[KSYM_NAME_LEN];
	int i;

	if (prog->aux->func_cnt == 0) {
		bpf_get_prog_name(prog, sym);
		perf_event_ksymbol(PERF_RECORD_KSYMBOL_TYPE_BPF,
				   (u64)(unsigned long)prog->bpf_func,
				   prog->jited_len, unregister, sym);
	} else {
		for (i = 0; i < prog->aux->func_cnt; i++) {
			struct bpf_prog *subprog = prog->aux->func[i];

			bpf_get_prog_name(subprog, sym);
			perf_event_ksymbol(
				PERF_RECORD_KSYMBOL_TYPE_BPF,
				(u64)(unsigned long)subprog->bpf_func,
				subprog->jited_len, unregister, sym);
		}
	}
}