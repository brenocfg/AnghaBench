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
struct dlm_ls {int /*<<< orphan*/  ls_ops_arg; TYPE_1__* ls_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* recover_prep ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dlm_lsop_recover_prep(struct dlm_ls *ls)
{
	if (!ls->ls_ops || !ls->ls_ops->recover_prep)
		return;
	ls->ls_ops->recover_prep(ls->ls_ops_arg);
}