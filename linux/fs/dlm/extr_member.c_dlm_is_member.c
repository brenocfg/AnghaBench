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
struct dlm_ls {int /*<<< orphan*/  ls_nodes; } ;

/* Variables and functions */
 scalar_t__ find_memb (int /*<<< orphan*/ *,int) ; 

int dlm_is_member(struct dlm_ls *ls, int nodeid)
{
	if (find_memb(&ls->ls_nodes, nodeid))
		return 1;
	return 0;
}