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
struct zfcp_fsf_req {int /*<<< orphan*/  status; TYPE_2__* adapter; } ;
struct TYPE_4__ {TYPE_1__* ccw_device; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_STATUS_FSFREQ_ERROR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_shutdown (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void zfcp_fsf_class_not_supp(struct zfcp_fsf_req *req)
{
	dev_err(&req->adapter->ccw_device->dev, "FCP device not "
		"operational because of an unsupported FC class\n");
	zfcp_erp_adapter_shutdown(req->adapter, 0, "fscns_1");
	req->status |= ZFCP_STATUS_FSFREQ_ERROR;
}