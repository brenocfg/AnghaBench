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
struct cls_mall_head {int /*<<< orphan*/  pf; int /*<<< orphan*/  exts; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cls_mall_head*) ; 
 int /*<<< orphan*/  tcf_exts_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_exts_put_net (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __mall_destroy(struct cls_mall_head *head)
{
	tcf_exts_destroy(&head->exts);
	tcf_exts_put_net(&head->exts);
	free_percpu(head->pf);
	kfree(head);
}