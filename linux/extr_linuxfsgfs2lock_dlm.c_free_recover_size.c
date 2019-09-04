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
struct lm_lockstruct {int /*<<< orphan*/ * ls_lvb_bits; scalar_t__ ls_recover_size; int /*<<< orphan*/ * ls_recover_result; int /*<<< orphan*/ * ls_recover_submit; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_recover_size(struct lm_lockstruct *ls)
{
	kfree(ls->ls_lvb_bits);
	kfree(ls->ls_recover_submit);
	kfree(ls->ls_recover_result);
	ls->ls_recover_submit = NULL;
	ls->ls_recover_result = NULL;
	ls->ls_recover_size = 0;
	ls->ls_lvb_bits = NULL;
}