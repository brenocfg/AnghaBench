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
struct idpair {int dummy; } ;
struct bpf_func_state {int /*<<< orphan*/ * regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ID_MAP_SIZE ; 
 int MAX_BPF_REG ; 
 struct idpair* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct idpair*) ; 
 int /*<<< orphan*/  refsafe (struct bpf_func_state*,struct bpf_func_state*) ; 
 int /*<<< orphan*/  regsafe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct idpair*) ; 
 int /*<<< orphan*/  stacksafe (struct bpf_func_state*,struct bpf_func_state*,struct idpair*) ; 

__attribute__((used)) static bool func_states_equal(struct bpf_func_state *old,
			      struct bpf_func_state *cur)
{
	struct idpair *idmap;
	bool ret = false;
	int i;

	idmap = kcalloc(ID_MAP_SIZE, sizeof(struct idpair), GFP_KERNEL);
	/* If we failed to allocate the idmap, just say it's not safe */
	if (!idmap)
		return false;

	for (i = 0; i < MAX_BPF_REG; i++) {
		if (!regsafe(&old->regs[i], &cur->regs[i], idmap))
			goto out_free;
	}

	if (!stacksafe(old, cur, idmap))
		goto out_free;

	if (!refsafe(old, cur))
		goto out_free;
	ret = true;
out_free:
	kfree(idmap);
	return ret;
}