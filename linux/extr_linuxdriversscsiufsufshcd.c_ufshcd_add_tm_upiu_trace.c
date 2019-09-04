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
struct utp_upiu_task_req {int /*<<< orphan*/  input_param1; int /*<<< orphan*/  header; } ;
struct utp_task_req_desc {scalar_t__ task_req_upiu; } ;
struct ufs_hba {int nutrs; int /*<<< orphan*/  dev; struct utp_task_req_desc* utmrdl_base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ufshcd_upiu (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ufshcd_add_tm_upiu_trace(struct ufs_hba *hba, unsigned int tag,
		const char *str)
{
	struct utp_task_req_desc *descp;
	struct utp_upiu_task_req *task_req;
	int off = (int)tag - hba->nutrs;

	descp = &hba->utmrdl_base_addr[off];
	task_req = (struct utp_upiu_task_req *)descp->task_req_upiu;
	trace_ufshcd_upiu(dev_name(hba->dev), str, &task_req->header,
			&task_req->input_param1);
}