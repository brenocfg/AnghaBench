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
struct cls_cgroup_head {int /*<<< orphan*/  exts; int /*<<< orphan*/  ematches; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct cls_cgroup_head*) ; 
 int /*<<< orphan*/  tcf_em_tree_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_exts_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_exts_put_net (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __cls_cgroup_destroy(struct cls_cgroup_head *head)
{
	tcf_exts_destroy(&head->exts);
	tcf_em_tree_destroy(&head->ematches);
	tcf_exts_put_net(&head->exts);
	kfree(head);
}