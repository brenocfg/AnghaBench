#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct nvmet_req {TYPE_5__* ops; scalar_t__ ns; TYPE_4__* cmd; TYPE_2__* rsp; TYPE_1__* sq; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* queue_response ) (struct nvmet_req*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  command_id; } ;
struct TYPE_9__ {TYPE_3__ common; } ;
struct TYPE_7__ {int /*<<< orphan*/  command_id; void* sq_id; void* sq_head; } ;
struct TYPE_6__ {int size; int sqhd; int qid; } ;

/* Variables and functions */
 int cmpxchg (int*,int,int) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  nvmet_put_namespace (scalar_t__) ; 
 int /*<<< orphan*/  nvmet_set_status (struct nvmet_req*,int) ; 
 int /*<<< orphan*/  stub1 (struct nvmet_req*) ; 

__attribute__((used)) static void __nvmet_req_complete(struct nvmet_req *req, u16 status)
{
	u32 old_sqhd, new_sqhd;
	u16 sqhd;

	if (status)
		nvmet_set_status(req, status);

	if (req->sq->size) {
		do {
			old_sqhd = req->sq->sqhd;
			new_sqhd = (old_sqhd + 1) % req->sq->size;
		} while (cmpxchg(&req->sq->sqhd, old_sqhd, new_sqhd) !=
					old_sqhd);
	}
	sqhd = req->sq->sqhd & 0x0000FFFF;
	req->rsp->sq_head = cpu_to_le16(sqhd);
	req->rsp->sq_id = cpu_to_le16(req->sq->qid);
	req->rsp->command_id = req->cmd->common.command_id;

	if (req->ns)
		nvmet_put_namespace(req->ns);
	req->ops->queue_response(req);
}