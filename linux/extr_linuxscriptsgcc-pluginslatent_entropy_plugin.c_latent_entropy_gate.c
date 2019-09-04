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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {int /*<<< orphan*/  preds; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 scalar_t__ EDGE_COUNT (int /*<<< orphan*/ ) ; 
 TYPE_1__* EXIT_BLOCK_PTR_FOR_FN (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_THIS_VOLATILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfun ; 
 int /*<<< orphan*/  current_function_decl ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool latent_entropy_gate(void)
{
	tree list;

	/* don't bother with noreturn functions for now */
	if (TREE_THIS_VOLATILE(current_function_decl))
		return false;

	/* gcc-4.5 doesn't discover some trivial noreturn functions */
	if (EDGE_COUNT(EXIT_BLOCK_PTR_FOR_FN(cfun)->preds) == 0)
		return false;

	list = DECL_ATTRIBUTES(current_function_decl);
	return lookup_attribute("latent_entropy", list) != NULL_TREE;
}