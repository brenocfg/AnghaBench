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
struct sp_node {int /*<<< orphan*/  nd; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct shared_policy {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sp_free (struct sp_node*) ; 

__attribute__((used)) static void sp_delete(struct shared_policy *sp, struct sp_node *n)
{
	pr_debug("deleting %lx-l%lx\n", n->start, n->end);
	rb_erase(&n->nd, &sp->root);
	sp_free(n);
}