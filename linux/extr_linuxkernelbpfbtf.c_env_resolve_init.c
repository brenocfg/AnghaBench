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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct btf_verifier_env {scalar_t__* visit_states; struct btf* btf; } ;
struct btf {scalar_t__* resolved_ids; scalar_t__* resolved_sizes; scalar_t__ nr_types; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int __GFP_NOWARN ; 
 scalar_t__* kvcalloc (scalar_t__,int,int) ; 
 int /*<<< orphan*/  kvfree (scalar_t__*) ; 

__attribute__((used)) static int env_resolve_init(struct btf_verifier_env *env)
{
	struct btf *btf = env->btf;
	u32 nr_types = btf->nr_types;
	u32 *resolved_sizes = NULL;
	u32 *resolved_ids = NULL;
	u8 *visit_states = NULL;

	/* +1 for btf_void */
	resolved_sizes = kvcalloc(nr_types + 1, sizeof(*resolved_sizes),
				  GFP_KERNEL | __GFP_NOWARN);
	if (!resolved_sizes)
		goto nomem;

	resolved_ids = kvcalloc(nr_types + 1, sizeof(*resolved_ids),
				GFP_KERNEL | __GFP_NOWARN);
	if (!resolved_ids)
		goto nomem;

	visit_states = kvcalloc(nr_types + 1, sizeof(*visit_states),
				GFP_KERNEL | __GFP_NOWARN);
	if (!visit_states)
		goto nomem;

	btf->resolved_sizes = resolved_sizes;
	btf->resolved_ids = resolved_ids;
	env->visit_states = visit_states;

	return 0;

nomem:
	kvfree(resolved_sizes);
	kvfree(resolved_ids);
	kvfree(visit_states);
	return -ENOMEM;
}