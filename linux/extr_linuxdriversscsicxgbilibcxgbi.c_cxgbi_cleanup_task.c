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
struct iscsi_tcp_task {struct cxgbi_task_data* dd_data; } ;
struct iscsi_task {int /*<<< orphan*/  hdr_itt; int /*<<< orphan*/ * hdr; int /*<<< orphan*/  sc; struct iscsi_tcp_task* dd_data; } ;
struct cxgbi_task_data {int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 int CXGBI_DBG_ISCSI ; 
 int /*<<< orphan*/  __kfree_skb (int /*<<< orphan*/ *) ; 
 struct cxgbi_task_data* iscsi_task_cxgbi_data (struct iscsi_task*) ; 
 int /*<<< orphan*/  iscsi_tcp_cleanup_task (struct iscsi_task*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct iscsi_task*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cxgbi_task_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,struct iscsi_task*,int /*<<< orphan*/ ,struct iscsi_tcp_task*,struct cxgbi_task_data*,struct cxgbi_task_data*) ; 
 int /*<<< orphan*/  task_release_itt (struct iscsi_task*,int /*<<< orphan*/ ) ; 

void cxgbi_cleanup_task(struct iscsi_task *task)
{
	struct iscsi_tcp_task *tcp_task = task->dd_data;
	struct cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);

	if (!tcp_task || !tdata || (tcp_task->dd_data != tdata)) {
		pr_info("task 0x%p,0x%p, tcp_task 0x%p, tdata 0x%p/0x%p.\n",
			task, task->sc, tcp_task,
			tcp_task ? tcp_task->dd_data : NULL, tdata);
		return;
	}

	log_debug(1 << CXGBI_DBG_ISCSI,
		"task 0x%p, skb 0x%p, itt 0x%x.\n",
		task, tdata->skb, task->hdr_itt);

	tcp_task->dd_data = NULL;

	if (!task->sc)
		kfree(task->hdr);
	task->hdr = NULL;

	/*  never reached the xmit task callout */
	if (tdata->skb) {
		__kfree_skb(tdata->skb);
		tdata->skb = NULL;
	}

	task_release_itt(task, task->hdr_itt);
	memset(tdata, 0, sizeof(*tdata));

	iscsi_tcp_cleanup_task(task);
}