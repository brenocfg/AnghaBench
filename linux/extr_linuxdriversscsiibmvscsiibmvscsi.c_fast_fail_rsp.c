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
typedef  scalar_t__ u16 ;
struct srp_event_struct {TYPE_4__* xfer_iu; struct ibmvscsi_host_data* hostdata; } ;
struct ibmvscsi_host_data {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; } ;
struct TYPE_6__ {TYPE_1__ common; } ;
struct TYPE_7__ {TYPE_2__ fast_fail; } ;
struct TYPE_8__ {TYPE_3__ mad; } ;

/* Variables and functions */
 scalar_t__ VIOSRP_MAD_FAILED ; 
 scalar_t__ VIOSRP_MAD_NOT_SUPPORTED ; 
 scalar_t__ VIOSRP_MAD_SUCCESS ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  send_mad_capabilities (struct ibmvscsi_host_data*) ; 

__attribute__((used)) static void fast_fail_rsp(struct srp_event_struct *evt_struct)
{
	struct ibmvscsi_host_data *hostdata = evt_struct->hostdata;
	u16 status = be16_to_cpu(evt_struct->xfer_iu->mad.fast_fail.common.status);

	if (status == VIOSRP_MAD_NOT_SUPPORTED)
		dev_err(hostdata->dev, "fast_fail not supported in server\n");
	else if (status == VIOSRP_MAD_FAILED)
		dev_err(hostdata->dev, "fast_fail request failed\n");
	else if (status != VIOSRP_MAD_SUCCESS)
		dev_err(hostdata->dev, "error 0x%X enabling fast_fail\n", status);

	send_mad_capabilities(hostdata);
}