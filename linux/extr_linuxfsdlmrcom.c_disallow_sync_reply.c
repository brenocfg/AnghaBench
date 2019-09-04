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
struct dlm_ls {int /*<<< orphan*/  ls_rcom_spin; int /*<<< orphan*/  ls_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSFL_RCOM_READY ; 
 int /*<<< orphan*/  LSFL_RCOM_WAIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disallow_sync_reply(struct dlm_ls *ls)
{
	spin_lock(&ls->ls_rcom_spin);
	clear_bit(LSFL_RCOM_WAIT, &ls->ls_flags);
	clear_bit(LSFL_RCOM_READY, &ls->ls_flags);
	spin_unlock(&ls->ls_rcom_spin);
}