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
struct nvmet_req {scalar_t__ data_len; scalar_t__ transfer_len; int /*<<< orphan*/  (* execute ) (struct nvmet_req*) ;} ;

/* Variables and functions */
 int NVME_SC_DNR ; 
 int NVME_SC_SGL_INVALID_DATA ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int) ; 
 int /*<<< orphan*/  stub1 (struct nvmet_req*) ; 
 scalar_t__ unlikely (int) ; 

void nvmet_req_execute(struct nvmet_req *req)
{
	if (unlikely(req->data_len != req->transfer_len))
		nvmet_req_complete(req, NVME_SC_SGL_INVALID_DATA | NVME_SC_DNR);
	else
		req->execute(req);
}