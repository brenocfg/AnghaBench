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
typedef  scalar_t__ uint32_t ;
struct dlm_message {scalar_t__ m_type; } ;
struct dlm_ls {int /*<<< orphan*/  ls_count; } ;

/* Variables and functions */
 scalar_t__ DLM_MSG_LOOKUP ; 
 scalar_t__ DLM_MSG_LOOKUP_REPLY ; 
 scalar_t__ DLM_MSG_REMOVE ; 
 scalar_t__ dlm_is_removed (struct dlm_ls*,int) ; 
 int /*<<< orphan*/  dlm_no_directory (struct dlm_ls*) ; 

__attribute__((used)) static int purge_request(struct dlm_ls *ls, struct dlm_message *ms, int nodeid)
{
	uint32_t type = ms->m_type;

	/* the ls is being cleaned up and freed by release_lockspace */
	if (!ls->ls_count)
		return 1;

	if (dlm_is_removed(ls, nodeid))
		return 1;

	/* directory operations are always purged because the directory is
	   always rebuilt during recovery and the lookups resent */

	if (type == DLM_MSG_REMOVE ||
	    type == DLM_MSG_LOOKUP ||
	    type == DLM_MSG_LOOKUP_REPLY)
		return 1;

	if (!dlm_no_directory(ls))
		return 0;

	return 1;
}