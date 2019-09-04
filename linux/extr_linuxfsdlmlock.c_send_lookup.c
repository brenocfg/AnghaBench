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
struct dlm_rsb {int dummy; } ;
struct dlm_mhandle {int dummy; } ;
struct dlm_message {int dummy; } ;
struct dlm_lkb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_MSG_LOOKUP ; 
 int /*<<< orphan*/  DLM_MSG_LOOKUP_REPLY ; 
 int add_to_waiters (struct dlm_lkb*,int /*<<< orphan*/ ,int) ; 
 int create_message (struct dlm_rsb*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct dlm_message**,struct dlm_mhandle**) ; 
 int dlm_dir_nodeid (struct dlm_rsb*) ; 
 int /*<<< orphan*/  remove_from_waiters (struct dlm_lkb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_args (struct dlm_rsb*,struct dlm_lkb*,struct dlm_message*) ; 
 int send_message (struct dlm_mhandle*,struct dlm_message*) ; 

__attribute__((used)) static int send_lookup(struct dlm_rsb *r, struct dlm_lkb *lkb)
{
	struct dlm_message *ms;
	struct dlm_mhandle *mh;
	int to_nodeid, error;

	to_nodeid = dlm_dir_nodeid(r);

	error = add_to_waiters(lkb, DLM_MSG_LOOKUP, to_nodeid);
	if (error)
		return error;

	error = create_message(r, NULL, to_nodeid, DLM_MSG_LOOKUP, &ms, &mh);
	if (error)
		goto fail;

	send_args(r, lkb, ms);

	error = send_message(mh, ms);
	if (error)
		goto fail;
	return 0;

 fail:
	remove_from_waiters(lkb, DLM_MSG_LOOKUP_REPLY);
	return error;
}