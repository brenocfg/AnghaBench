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
struct policydb {int /*<<< orphan*/  cond_list; int /*<<< orphan*/  te_cond_avtab; int /*<<< orphan*/  bool_val_to_struct; } ;

/* Variables and functions */
 int /*<<< orphan*/  avtab_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_list_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void cond_policydb_destroy(struct policydb *p)
{
	kfree(p->bool_val_to_struct);
	avtab_destroy(&p->te_cond_avtab);
	cond_list_destroy(p->cond_list);
}