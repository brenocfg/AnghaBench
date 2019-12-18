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
struct dlm_rsb {scalar_t__ res_id; int /*<<< orphan*/  res_length; int /*<<< orphan*/  res_name; struct dlm_ls* res_ls; } ;
struct dlm_rcom {unsigned long rc_id; int /*<<< orphan*/  rc_buf; } ;
struct dlm_mhandle {int dummy; } ;
struct dlm_ls {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_RCOM_LOOKUP ; 
 int create_rcom (struct dlm_ls*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_rcom**,struct dlm_mhandle**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_rcom (struct dlm_ls*,struct dlm_mhandle*,struct dlm_rcom*) ; 

int dlm_send_rcom_lookup(struct dlm_rsb *r, int dir_nodeid)
{
	struct dlm_rcom *rc;
	struct dlm_mhandle *mh;
	struct dlm_ls *ls = r->res_ls;
	int error;

	error = create_rcom(ls, dir_nodeid, DLM_RCOM_LOOKUP, r->res_length,
			    &rc, &mh);
	if (error)
		goto out;
	memcpy(rc->rc_buf, r->res_name, r->res_length);
	rc->rc_id = (unsigned long) r->res_id;

	send_rcom(ls, mh, rc);
 out:
	return error;
}