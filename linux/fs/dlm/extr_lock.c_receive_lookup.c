#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int h_nodeid; } ;
struct dlm_message {int /*<<< orphan*/  m_extra; TYPE_1__ m_header; } ;
struct dlm_ls {int dummy; } ;

/* Variables and functions */
 int dlm_master_lookup (struct dlm_ls*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int dlm_our_nodeid () ; 
 int receive_extralen (struct dlm_message*) ; 
 int /*<<< orphan*/  receive_request (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  send_lookup_reply (struct dlm_ls*,struct dlm_message*,int,int) ; 

__attribute__((used)) static void receive_lookup(struct dlm_ls *ls, struct dlm_message *ms)
{
	int len, error, ret_nodeid, from_nodeid, our_nodeid;

	from_nodeid = ms->m_header.h_nodeid;
	our_nodeid = dlm_our_nodeid();

	len = receive_extralen(ms);

	error = dlm_master_lookup(ls, from_nodeid, ms->m_extra, len, 0,
				  &ret_nodeid, NULL);

	/* Optimization: we're master so treat lookup as a request */
	if (!error && ret_nodeid == our_nodeid) {
		receive_request(ls, ms);
		return;
	}
	send_lookup_reply(ls, ms, ret_nodeid, error);
}