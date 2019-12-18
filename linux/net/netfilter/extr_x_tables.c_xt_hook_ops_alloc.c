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
typedef  size_t uint8_t ;
struct xt_table {unsigned int valid_hooks; int /*<<< orphan*/  priority; int /*<<< orphan*/  af; } ;
struct nf_hook_ops {size_t hooknum; int /*<<< orphan*/  priority; int /*<<< orphan*/  pf; int /*<<< orphan*/ * hook; } ;
typedef  int /*<<< orphan*/  nf_hookfn ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct nf_hook_ops* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t hweight32 (unsigned int) ; 
 struct nf_hook_ops* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 

struct nf_hook_ops *
xt_hook_ops_alloc(const struct xt_table *table, nf_hookfn *fn)
{
	unsigned int hook_mask = table->valid_hooks;
	uint8_t i, num_hooks = hweight32(hook_mask);
	uint8_t hooknum;
	struct nf_hook_ops *ops;

	if (!num_hooks)
		return ERR_PTR(-EINVAL);

	ops = kcalloc(num_hooks, sizeof(*ops), GFP_KERNEL);
	if (ops == NULL)
		return ERR_PTR(-ENOMEM);

	for (i = 0, hooknum = 0; i < num_hooks && hook_mask != 0;
	     hook_mask >>= 1, ++hooknum) {
		if (!(hook_mask & 1))
			continue;
		ops[i].hook     = fn;
		ops[i].pf       = table->af;
		ops[i].hooknum  = hooknum;
		ops[i].priority = table->priority;
		++i;
	}

	return ops;
}