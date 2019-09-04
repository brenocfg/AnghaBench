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
struct nvme_ctrl {TYPE_1__* opts; } ;
struct TYPE_2__ {int mask; char* traddr; char* trsvcid; char* host_traddr; } ;

/* Variables and functions */
 int NVMF_OPT_HOST_TRADDR ; 
 int NVMF_OPT_TRADDR ; 
 int NVMF_OPT_TRSVCID ; 
 scalar_t__ snprintf (char*,int,char*,...) ; 

int nvmf_get_address(struct nvme_ctrl *ctrl, char *buf, int size)
{
	int len = 0;

	if (ctrl->opts->mask & NVMF_OPT_TRADDR)
		len += snprintf(buf, size, "traddr=%s", ctrl->opts->traddr);
	if (ctrl->opts->mask & NVMF_OPT_TRSVCID)
		len += snprintf(buf + len, size - len, "%strsvcid=%s",
				(len) ? "," : "", ctrl->opts->trsvcid);
	if (ctrl->opts->mask & NVMF_OPT_HOST_TRADDR)
		len += snprintf(buf + len, size - len, "%shost_traddr=%s",
				(len) ? "," : "", ctrl->opts->host_traddr);
	len += snprintf(buf + len, size - len, "\n");

	return len;
}