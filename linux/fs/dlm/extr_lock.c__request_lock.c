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
struct dlm_lkb {int dummy; } ;

/* Variables and functions */
 int do_request (struct dlm_rsb*,struct dlm_lkb*) ; 
 int /*<<< orphan*/  do_request_effects (struct dlm_rsb*,struct dlm_lkb*,int) ; 
 scalar_t__ is_remote (struct dlm_rsb*) ; 
 int send_request (struct dlm_rsb*,struct dlm_lkb*) ; 
 int set_master (struct dlm_rsb*,struct dlm_lkb*) ; 

__attribute__((used)) static int _request_lock(struct dlm_rsb *r, struct dlm_lkb *lkb)
{
	int error;

	/* set_master: sets lkb nodeid from r */

	error = set_master(r, lkb);
	if (error < 0)
		goto out;
	if (error) {
		error = 0;
		goto out;
	}

	if (is_remote(r)) {
		/* receive_request() calls do_request() on remote node */
		error = send_request(r, lkb);
	} else {
		error = do_request(r, lkb);
		/* for remote locks the request_reply is sent
		   between do_request and do_request_effects */
		do_request_effects(r, lkb, error);
	}
 out:
	return error;
}