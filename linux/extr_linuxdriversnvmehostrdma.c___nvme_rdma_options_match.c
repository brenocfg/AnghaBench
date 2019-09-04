#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvmf_ctrl_options {char* traddr; int mask; char* trsvcid; char* host_traddr; } ;
struct TYPE_4__ {TYPE_1__* opts; } ;
struct nvme_rdma_ctrl {TYPE_2__ ctrl; } ;
struct TYPE_3__ {char* traddr; int mask; char* trsvcid; char* host_traddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_RDMA_IP_PORT ; 
 int NVMF_OPT_HOST_TRADDR ; 
 int NVMF_OPT_TRSVCID ; 
 char* __stringify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmf_ctlr_matches_baseopts (TYPE_2__*,struct nvmf_ctrl_options*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static inline bool
__nvme_rdma_options_match(struct nvme_rdma_ctrl *ctrl,
	struct nvmf_ctrl_options *opts)
{
	char *stdport = __stringify(NVME_RDMA_IP_PORT);


	if (!nvmf_ctlr_matches_baseopts(&ctrl->ctrl, opts) ||
	    strcmp(opts->traddr, ctrl->ctrl.opts->traddr))
		return false;

	if (opts->mask & NVMF_OPT_TRSVCID &&
	    ctrl->ctrl.opts->mask & NVMF_OPT_TRSVCID) {
		if (strcmp(opts->trsvcid, ctrl->ctrl.opts->trsvcid))
			return false;
	} else if (opts->mask & NVMF_OPT_TRSVCID) {
		if (strcmp(opts->trsvcid, stdport))
			return false;
	} else if (ctrl->ctrl.opts->mask & NVMF_OPT_TRSVCID) {
		if (strcmp(stdport, ctrl->ctrl.opts->trsvcid))
			return false;
	}
	/* else, it's a match as both have stdport. Fall to next checks */

	/*
	 * checking the local address is rough. In most cases, one
	 * is not specified and the host port is selected by the stack.
	 *
	 * Assume no match if:
	 *  local address is specified and address is not the same
	 *  local address is not specified but remote is, or vice versa
	 *    (admin using specific host_traddr when it matters).
	 */
	if (opts->mask & NVMF_OPT_HOST_TRADDR &&
	    ctrl->ctrl.opts->mask & NVMF_OPT_HOST_TRADDR) {
		if (strcmp(opts->host_traddr, ctrl->ctrl.opts->host_traddr))
			return false;
	} else if (opts->mask & NVMF_OPT_HOST_TRADDR ||
		   ctrl->ctrl.opts->mask & NVMF_OPT_HOST_TRADDR)
		return false;
	/*
	 * if neither controller had an host port specified, assume it's
	 * a match as everything else matched.
	 */

	return true;
}