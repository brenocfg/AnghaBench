#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* basic_block ;
struct TYPE_7__ {struct TYPE_7__* next_bb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_BLOCK_PTR_FOR_FN (int /*<<< orphan*/ ) ; 
 TYPE_1__* EXIT_BLOCK_PTR_FOR_FN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfun ; 
 int /*<<< orphan*/  create_latent_entropy_decl () ; 
 int /*<<< orphan*/  create_var (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_local_entropy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  long_unsigned_type_node ; 
 int /*<<< orphan*/  perturb_latent_entropy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perturb_local_entropy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  single_pred_p (TYPE_1__*) ; 
 TYPE_1__* single_succ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  single_succ_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  single_succ_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  split_edge (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int latent_entropy_execute(void)
{
	basic_block bb;
	tree local_entropy;

	if (!create_latent_entropy_decl())
		return 0;

	/* prepare for step 2 below */
	gcc_assert(single_succ_p(ENTRY_BLOCK_PTR_FOR_FN(cfun)));
	bb = single_succ(ENTRY_BLOCK_PTR_FOR_FN(cfun));
	if (!single_pred_p(bb)) {
		split_edge(single_succ_edge(ENTRY_BLOCK_PTR_FOR_FN(cfun)));
		gcc_assert(single_succ_p(ENTRY_BLOCK_PTR_FOR_FN(cfun)));
		bb = single_succ(ENTRY_BLOCK_PTR_FOR_FN(cfun));
	}

	/* 1. create the local entropy variable */
	local_entropy = create_var(long_unsigned_type_node, "local_entropy");

	/* 2. initialize the local entropy variable */
	init_local_entropy(bb, local_entropy);

	bb = bb->next_bb;

	/*
	 * 3. instrument each BB with an operation on the
	 *    local entropy variable
	 */
	while (bb != EXIT_BLOCK_PTR_FOR_FN(cfun)) {
		perturb_local_entropy(bb, local_entropy);
		bb = bb->next_bb;
	};

	/* 4. mix local entropy into the global entropy variable */
	perturb_latent_entropy(local_entropy);
	return 0;
}