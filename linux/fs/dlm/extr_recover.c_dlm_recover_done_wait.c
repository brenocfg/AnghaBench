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
struct dlm_ls {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_RS_DONE ; 
 int wait_status (struct dlm_ls*,int /*<<< orphan*/ ) ; 

int dlm_recover_done_wait(struct dlm_ls *ls)
{
	return wait_status(ls, DLM_RS_DONE);
}