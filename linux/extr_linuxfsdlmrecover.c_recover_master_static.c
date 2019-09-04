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
struct dlm_rsb {int res_master_nodeid; int res_nodeid; } ;

/* Variables and functions */
 int dlm_dir_nodeid (struct dlm_rsb*) ; 
 int dlm_our_nodeid () ; 
 int /*<<< orphan*/  dlm_purge_mstcpy_locks (struct dlm_rsb*) ; 
 int /*<<< orphan*/  set_new_master (struct dlm_rsb*) ; 

__attribute__((used)) static int recover_master_static(struct dlm_rsb *r, unsigned int *count)
{
	int dir_nodeid = dlm_dir_nodeid(r);
	int new_master = dir_nodeid;

	if (dir_nodeid == dlm_our_nodeid())
		new_master = 0;

	dlm_purge_mstcpy_locks(r);
	r->res_master_nodeid = dir_nodeid;
	r->res_nodeid = new_master;
	set_new_master(r);
	(*count)++;
	return 0;
}