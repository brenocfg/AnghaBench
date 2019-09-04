#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nsim_bpf_bound_prog {char* state; int /*<<< orphan*/  l; int /*<<< orphan*/  is_loaded; int /*<<< orphan*/  ddir; struct bpf_prog* prog; struct netdevsim* ns; } ;
struct netdevsim {TYPE_1__* sdev; } ;
struct bpf_prog {TYPE_3__* aux; } ;
struct TYPE_6__ {TYPE_2__* offload; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {struct nsim_bpf_bound_prog* dev_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  bpf_bound_progs; int /*<<< orphan*/  ddir_bpf_bound_progs; int /*<<< orphan*/  prog_id_gen; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nsim_bpf_bound_prog*) ; 
 struct nsim_bpf_bound_prog* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsim_bpf_string_fops ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nsim_bpf_create_prog(struct netdevsim *ns, struct bpf_prog *prog)
{
	struct nsim_bpf_bound_prog *state;
	char name[16];

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return -ENOMEM;

	state->ns = ns;
	state->prog = prog;
	state->state = "verify";

	/* Program id is not populated yet when we create the state. */
	sprintf(name, "%u", ns->sdev->prog_id_gen++);
	state->ddir = debugfs_create_dir(name, ns->sdev->ddir_bpf_bound_progs);
	if (IS_ERR_OR_NULL(state->ddir)) {
		kfree(state);
		return -ENOMEM;
	}

	debugfs_create_u32("id", 0400, state->ddir, &prog->aux->id);
	debugfs_create_file("state", 0400, state->ddir,
			    &state->state, &nsim_bpf_string_fops);
	debugfs_create_bool("loaded", 0400, state->ddir, &state->is_loaded);

	list_add_tail(&state->l, &ns->sdev->bpf_bound_progs);

	prog->aux->offload->dev_priv = state;

	return 0;
}