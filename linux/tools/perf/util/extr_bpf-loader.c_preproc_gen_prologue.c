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
struct probe_trace_event {int /*<<< orphan*/  nargs; int /*<<< orphan*/  args; } ;
struct perf_probe_event {int ntevs; struct probe_trace_event* tevs; } ;
struct bpf_program {int dummy; } ;
struct bpf_prog_priv {int nr_types; int* type_mapping; struct bpf_insn* insns_buf; struct perf_probe_event pev; scalar_t__ is_tp; } ;
struct bpf_prog_prep_result {size_t new_insn_cnt; int /*<<< orphan*/ * pfd; struct bpf_insn* new_insn_ptr; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 int BPF_LOADER_ERRNO__PROLOGUE ; 
 scalar_t__ BPF_MAXINSNS ; 
 scalar_t__ IS_ERR (struct bpf_prog_priv*) ; 
 int bpf__gen_prologue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bpf_insn*,size_t*,scalar_t__) ; 
 struct bpf_prog_priv* bpf_program__priv (struct bpf_program*) ; 
 char* bpf_program__title (struct bpf_program*,int) ; 
 int /*<<< orphan*/  memcpy (struct bpf_insn*,struct bpf_insn*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int
preproc_gen_prologue(struct bpf_program *prog, int n,
		     struct bpf_insn *orig_insns, int orig_insns_cnt,
		     struct bpf_prog_prep_result *res)
{
	struct bpf_prog_priv *priv = bpf_program__priv(prog);
	struct probe_trace_event *tev;
	struct perf_probe_event *pev;
	struct bpf_insn *buf;
	size_t prologue_cnt = 0;
	int i, err;

	if (IS_ERR(priv) || !priv || priv->is_tp)
		goto errout;

	pev = &priv->pev;

	if (n < 0 || n >= priv->nr_types)
		goto errout;

	/* Find a tev belongs to that type */
	for (i = 0; i < pev->ntevs; i++) {
		if (priv->type_mapping[i] == n)
			break;
	}

	if (i >= pev->ntevs) {
		pr_debug("Internal error: prologue type %d not found\n", n);
		return -BPF_LOADER_ERRNO__PROLOGUE;
	}

	tev = &pev->tevs[i];

	buf = priv->insns_buf;
	err = bpf__gen_prologue(tev->args, tev->nargs,
				buf, &prologue_cnt,
				BPF_MAXINSNS - orig_insns_cnt);
	if (err) {
		const char *title;

		title = bpf_program__title(prog, false);
		if (!title)
			title = "[unknown]";

		pr_debug("Failed to generate prologue for program %s\n",
			 title);
		return err;
	}

	memcpy(&buf[prologue_cnt], orig_insns,
	       sizeof(struct bpf_insn) * orig_insns_cnt);

	res->new_insn_ptr = buf;
	res->new_insn_cnt = prologue_cnt + orig_insns_cnt;
	res->pfd = NULL;
	return 0;

errout:
	pr_debug("Internal error in preproc_gen_prologue\n");
	return -BPF_LOADER_ERRNO__PROLOGUE;
}