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
struct rq_entry {int recover_seq; int nodeid; int /*<<< orphan*/  list; int /*<<< orphan*/  request; } ;
struct TYPE_2__ {int /*<<< orphan*/  h_length; } ;
struct dlm_message {TYPE_1__ m_header; } ;
struct dlm_ls {int ls_recover_seq; int /*<<< orphan*/  ls_requestqueue_mutex; int /*<<< orphan*/  ls_requestqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct rq_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_print (char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dlm_message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void dlm_add_requestqueue(struct dlm_ls *ls, int nodeid, struct dlm_message *ms)
{
	struct rq_entry *e;
	int length = ms->m_header.h_length - sizeof(struct dlm_message);

	e = kmalloc(sizeof(struct rq_entry) + length, GFP_NOFS);
	if (!e) {
		log_print("dlm_add_requestqueue: out of memory len %d", length);
		return;
	}

	e->recover_seq = ls->ls_recover_seq & 0xFFFFFFFF;
	e->nodeid = nodeid;
	memcpy(&e->request, ms, ms->m_header.h_length);

	mutex_lock(&ls->ls_requestqueue_mutex);
	list_add_tail(&e->list, &ls->ls_requestqueue);
	mutex_unlock(&ls->ls_requestqueue_mutex);
}