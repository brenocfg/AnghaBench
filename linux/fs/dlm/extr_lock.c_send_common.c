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
struct dlm_rsb {int res_nodeid; } ;
struct dlm_mhandle {int dummy; } ;
struct dlm_message {int dummy; } ;
struct dlm_lkb {int dummy; } ;

/* Variables and functions */
 int add_to_waiters (struct dlm_lkb*,int,int) ; 
 int create_message (struct dlm_rsb*,struct dlm_lkb*,int,int,struct dlm_message**,struct dlm_mhandle**) ; 
 int /*<<< orphan*/  msg_reply_type (int) ; 
 int /*<<< orphan*/  remove_from_waiters (struct dlm_lkb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_args (struct dlm_rsb*,struct dlm_lkb*,struct dlm_message*) ; 
 int send_message (struct dlm_mhandle*,struct dlm_message*) ; 

__attribute__((used)) static int send_common(struct dlm_rsb *r, struct dlm_lkb *lkb, int mstype)
{
	struct dlm_message *ms;
	struct dlm_mhandle *mh;
	int to_nodeid, error;

	to_nodeid = r->res_nodeid;

	error = add_to_waiters(lkb, mstype, to_nodeid);
	if (error)
		return error;

	error = create_message(r, lkb, to_nodeid, mstype, &ms, &mh);
	if (error)
		goto fail;

	send_args(r, lkb, ms);

	error = send_message(mh, ms);
	if (error)
		goto fail;
	return 0;

 fail:
	remove_from_waiters(lkb, msg_reply_type(mstype));
	return error;
}