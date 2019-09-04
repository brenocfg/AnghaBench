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
struct dlm_mhandle {int dummy; } ;
struct dlm_message {int m_nodeid; int m_pid; } ;
struct dlm_ls {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_MSG_PURGE ; 
 int _create_message (struct dlm_ls*,int,int,int /*<<< orphan*/ ,struct dlm_message**,struct dlm_mhandle**) ; 
 int send_message (struct dlm_mhandle*,struct dlm_message*) ; 

__attribute__((used)) static int send_purge(struct dlm_ls *ls, int nodeid, int pid)
{
	struct dlm_message *ms;
	struct dlm_mhandle *mh;
	int error;

	error = _create_message(ls, sizeof(struct dlm_message), nodeid,
				DLM_MSG_PURGE, &ms, &mh);
	if (error)
		return error;
	ms->m_nodeid = nodeid;
	ms->m_pid = pid;

	return send_message(mh, ms);
}