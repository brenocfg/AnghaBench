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
struct nvmet_req {int dummy; } ;
struct nvmet_fc_tgtport {int dummy; } ;
struct nvmet_fc_fcp_iod {struct nvmet_fc_tgtport* tgtport; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nvmet_fc_fcp_nvme_cmd_done (struct nvmet_fc_tgtport*,struct nvmet_fc_fcp_iod*,int /*<<< orphan*/ ) ; 
 struct nvmet_fc_fcp_iod* nvmet_req_to_fod (struct nvmet_req*) ; 

__attribute__((used)) static void
nvmet_fc_fcp_nvme_cmd_done(struct nvmet_req *nvme_req)
{
	struct nvmet_fc_fcp_iod *fod = nvmet_req_to_fod(nvme_req);
	struct nvmet_fc_tgtport *tgtport = fod->tgtport;

	__nvmet_fc_fcp_nvme_cmd_done(tgtport, fod, 0);
}