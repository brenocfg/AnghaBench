#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct utp_upiu_rsp {int dummy; } ;
struct TYPE_6__ {void* dword_2; void* dword_1; void* dword_0; } ;
struct utp_upiu_req {int /*<<< orphan*/  qr; TYPE_2__ header; } ;
struct ufshcd_lrb {int lun; int /*<<< orphan*/  ucd_rsp_ptr; int /*<<< orphan*/  task_tag; struct utp_upiu_req* ucd_req_ptr; } ;
struct TYPE_8__ {scalar_t__ opcode; int /*<<< orphan*/  length; } ;
struct TYPE_7__ {TYPE_4__ upiu_req; int /*<<< orphan*/  query_func; } ;
struct ufs_query {TYPE_4__* descriptor; TYPE_3__ request; } ;
struct TYPE_5__ {struct ufs_query query; } ;
struct ufs_hba {TYPE_1__ dev_cmd; } ;

/* Variables and functions */
 int GENERAL_UPIU_REQUEST_SIZE ; 
 int QUERY_OSF_SIZE ; 
 void* UPIU_HEADER_DWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ UPIU_QUERY_OPCODE_WRITE_DESC ; 
 int /*<<< orphan*/  UPIU_TRANSACTION_QUERY_REQ ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ufshcd_prepare_utp_query_req_upiu(struct ufs_hba *hba,
				struct ufshcd_lrb *lrbp, u32 upiu_flags)
{
	struct utp_upiu_req *ucd_req_ptr = lrbp->ucd_req_ptr;
	struct ufs_query *query = &hba->dev_cmd.query;
	u16 len = be16_to_cpu(query->request.upiu_req.length);
	u8 *descp = (u8 *)lrbp->ucd_req_ptr + GENERAL_UPIU_REQUEST_SIZE;

	/* Query request header */
	ucd_req_ptr->header.dword_0 = UPIU_HEADER_DWORD(
			UPIU_TRANSACTION_QUERY_REQ, upiu_flags,
			lrbp->lun, lrbp->task_tag);
	ucd_req_ptr->header.dword_1 = UPIU_HEADER_DWORD(
			0, query->request.query_func, 0, 0);

	/* Data segment length only need for WRITE_DESC */
	if (query->request.upiu_req.opcode == UPIU_QUERY_OPCODE_WRITE_DESC)
		ucd_req_ptr->header.dword_2 =
			UPIU_HEADER_DWORD(0, 0, (len >> 8), (u8)len);
	else
		ucd_req_ptr->header.dword_2 = 0;

	/* Copy the Query Request buffer as is */
	memcpy(&ucd_req_ptr->qr, &query->request.upiu_req,
			QUERY_OSF_SIZE);

	/* Copy the Descriptor */
	if (query->request.upiu_req.opcode == UPIU_QUERY_OPCODE_WRITE_DESC)
		memcpy(descp, query->descriptor, len);

	memset(lrbp->ucd_rsp_ptr, 0, sizeof(struct utp_upiu_rsp));
}