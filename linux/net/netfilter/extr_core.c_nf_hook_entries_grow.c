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
struct nf_hook_ops {scalar_t__ priority; int /*<<< orphan*/  priv; int /*<<< orphan*/  hook; } ;
typedef  struct nf_hook_entries {unsigned int num_hook_entries; TYPE_1__* hooks; } const nf_hook_entries ;
struct TYPE_2__ {int /*<<< orphan*/  priv; int /*<<< orphan*/  hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2BIG ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct nf_hook_entries const* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned int MAX_HOOK_COUNT ; 
 struct nf_hook_entries const* allocate_hook_entries_size (unsigned int) ; 
 struct nf_hook_ops dummy_ops ; 
 struct nf_hook_ops** nf_hook_entries_get_hook_ops (struct nf_hook_entries const*) ; 

__attribute__((used)) static struct nf_hook_entries *
nf_hook_entries_grow(const struct nf_hook_entries *old,
		     const struct nf_hook_ops *reg)
{
	unsigned int i, alloc_entries, nhooks, old_entries;
	struct nf_hook_ops **orig_ops = NULL;
	struct nf_hook_ops **new_ops;
	struct nf_hook_entries *new;
	bool inserted = false;

	alloc_entries = 1;
	old_entries = old ? old->num_hook_entries : 0;

	if (old) {
		orig_ops = nf_hook_entries_get_hook_ops(old);

		for (i = 0; i < old_entries; i++) {
			if (orig_ops[i] != &dummy_ops)
				alloc_entries++;
		}
	}

	if (alloc_entries > MAX_HOOK_COUNT)
		return ERR_PTR(-E2BIG);

	new = allocate_hook_entries_size(alloc_entries);
	if (!new)
		return ERR_PTR(-ENOMEM);

	new_ops = nf_hook_entries_get_hook_ops(new);

	i = 0;
	nhooks = 0;
	while (i < old_entries) {
		if (orig_ops[i] == &dummy_ops) {
			++i;
			continue;
		}

		if (inserted || reg->priority > orig_ops[i]->priority) {
			new_ops[nhooks] = (void *)orig_ops[i];
			new->hooks[nhooks] = old->hooks[i];
			i++;
		} else {
			new_ops[nhooks] = (void *)reg;
			new->hooks[nhooks].hook = reg->hook;
			new->hooks[nhooks].priv = reg->priv;
			inserted = true;
		}
		nhooks++;
	}

	if (!inserted) {
		new_ops[nhooks] = (void *)reg;
		new->hooks[nhooks].hook = reg->hook;
		new->hooks[nhooks].priv = reg->priv;
	}

	return new;
}