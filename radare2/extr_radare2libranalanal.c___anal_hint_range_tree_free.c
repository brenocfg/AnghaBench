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
 int /*<<< orphan*/  RAnalRange ; 
 int /*<<< orphan*/  container_of (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb ; 

__attribute__((used)) static void __anal_hint_range_tree_free(RBNode *node) {
	free (container_of (node, RAnalRange, rb));
}