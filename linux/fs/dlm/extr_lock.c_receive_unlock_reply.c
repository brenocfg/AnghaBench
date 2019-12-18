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
struct dlm_message {int /*<<< orphan*/  m_remid; } ;
struct dlm_ls {int dummy; } ;
struct dlm_lkb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _receive_unlock_reply (struct dlm_lkb*,struct dlm_message*) ; 
 int /*<<< orphan*/  dlm_put_lkb (struct dlm_lkb*) ; 
 int find_lkb (struct dlm_ls*,int /*<<< orphan*/ ,struct dlm_lkb**) ; 

__attribute__((used)) static int receive_unlock_reply(struct dlm_ls *ls, struct dlm_message *ms)
{
	struct dlm_lkb *lkb;
	int error;

	error = find_lkb(ls, ms->m_remid, &lkb);
	if (error)
		return error;

	_receive_unlock_reply(lkb, ms);
	dlm_put_lkb(lkb);
	return 0;
}