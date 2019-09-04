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
struct list_head {int dummy; } ;
struct bb_node {int /*<<< orphan*/  l; int /*<<< orphan*/  e_succs; int /*<<< orphan*/  e_prevs; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct bb_node* calloc (int,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  p_err (char*) ; 

__attribute__((used)) static struct bb_node *func_insert_dummy_bb(struct list_head *after)
{
	struct bb_node *bb;

	bb = calloc(1, sizeof(*bb));
	if (!bb) {
		p_err("OOM when allocating BB node");
		return NULL;
	}

	INIT_LIST_HEAD(&bb->e_prevs);
	INIT_LIST_HEAD(&bb->e_succs);
	list_add(&bb->l, after);

	return bb;
}