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
struct dlm_ls {int /*<<< orphan*/  ls_recover_idr_lock; scalar_t__ ls_recover_list_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int recover_idr_empty(struct dlm_ls *ls)
{
	int empty = 1;

	spin_lock(&ls->ls_recover_idr_lock);
	if (ls->ls_recover_list_count)
		empty = 0;
	spin_unlock(&ls->ls_recover_idr_lock);

	return empty;
}