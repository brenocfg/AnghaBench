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
typedef  int u16 ;
struct nvmet_req {int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int NVME_SC_DNR ; 
 int NVME_SC_SGL_INVALID_DATA ; 
 size_t sg_zero_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

u16 nvmet_zero_sgl(struct nvmet_req *req, off_t off, size_t len)
{
	if (sg_zero_buffer(req->sg, req->sg_cnt, len, off) != len)
		return NVME_SC_SGL_INVALID_DATA | NVME_SC_DNR;
	return 0;
}