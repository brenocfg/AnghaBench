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
struct dlm_ls {int /*<<< orphan*/  ls_in_recovery; } ;

/* Variables and functions */
 int down_read_trylock (int /*<<< orphan*/ *) ; 

int dlm_lock_recovery_try(struct dlm_ls *ls)
{
	return down_read_trylock(&ls->ls_in_recovery);
}