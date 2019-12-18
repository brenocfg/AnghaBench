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
struct dlm_ls {scalar_t__ ls_num_nodes; int /*<<< orphan*/  ls_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_memb_list (int /*<<< orphan*/ *) ; 

void dlm_clear_members(struct dlm_ls *ls)
{
	clear_memb_list(&ls->ls_nodes);
	ls->ls_num_nodes = 0;
}