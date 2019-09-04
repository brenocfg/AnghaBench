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
typedef  int /*<<< orphan*/  RBNode ;

/* Variables and functions */

__attribute__((used)) static void _fcn_tree_free(RBNode *node) {
	// TODO RB tree is an intrusive data structure by embedding RBNode into RAnalFunction.
	// Currently fcns takes the ownership of the resources.
	// If the ownership transfers from fcns to fcn_tree:
	//
	// r_anal_fcn_free (FCN_CONTAINER (node));
}