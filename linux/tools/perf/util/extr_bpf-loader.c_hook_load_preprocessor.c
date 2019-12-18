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
struct probe_trace_event {scalar_t__ nargs; } ;
struct perf_probe_event {int ntevs; struct probe_trace_event* tevs; } ;
struct bpf_program {int dummy; } ;
struct bpf_prog_priv {int need_prologue; int /*<<< orphan*/  nr_types; void* type_mapping; void* insns_buf; struct perf_probe_event pev; scalar_t__ is_tp; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 int BPF_LOADER_ERRNO__INTERNAL ; 
 int BPF_MAXINSNS ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct bpf_prog_priv*) ; 
 struct bpf_prog_priv* bpf_program__priv (struct bpf_program*) ; 
 int bpf_program__set_prep (struct bpf_program*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* malloc (int) ; 
 int map_prologue (struct perf_probe_event*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  preproc_gen_prologue ; 

__attribute__((used)) static int hook_load_preprocessor(struct bpf_program *prog)
{
	struct bpf_prog_priv *priv = bpf_program__priv(prog);
	struct perf_probe_event *pev;
	bool need_prologue = false;
	int err, i;

	if (IS_ERR(priv) || !priv) {
		pr_debug("Internal error when hook preprocessor\n");
		return -BPF_LOADER_ERRNO__INTERNAL;
	}

	if (priv->is_tp) {
		priv->need_prologue = false;
		return 0;
	}

	pev = &priv->pev;
	for (i = 0; i < pev->ntevs; i++) {
		struct probe_trace_event *tev = &pev->tevs[i];

		if (tev->nargs > 0) {
			need_prologue = true;
			break;
		}
	}

	/*
	 * Since all tevs don't have argument, we don't need generate
	 * prologue.
	 */
	if (!need_prologue) {
		priv->need_prologue = false;
		return 0;
	}

	priv->need_prologue = true;
	priv->insns_buf = malloc(sizeof(struct bpf_insn) * BPF_MAXINSNS);
	if (!priv->insns_buf) {
		pr_debug("Not enough memory: alloc insns_buf failed\n");
		return -ENOMEM;
	}

	priv->type_mapping = malloc(sizeof(int) * pev->ntevs);
	if (!priv->type_mapping) {
		pr_debug("Not enough memory: alloc type_mapping failed\n");
		return -ENOMEM;
	}
	memset(priv->type_mapping, -1,
	       sizeof(int) * pev->ntevs);

	err = map_prologue(pev, priv->type_mapping, &priv->nr_types);
	if (err)
		return err;

	err = bpf_program__set_prep(prog, priv->nr_types,
				    preproc_gen_prologue);
	return err;
}