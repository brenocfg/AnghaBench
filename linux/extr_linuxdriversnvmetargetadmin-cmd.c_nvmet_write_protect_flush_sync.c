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
typedef  scalar_t__ u16 ;
struct nvmet_req {TYPE_1__* ns; } ;
struct TYPE_2__ {int /*<<< orphan*/  nsid; scalar_t__ file; } ;

/* Variables and functions */
 scalar_t__ nvmet_bdev_flush (struct nvmet_req*) ; 
 scalar_t__ nvmet_file_flush (struct nvmet_req*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 nvmet_write_protect_flush_sync(struct nvmet_req *req)
{
	u16 status;

	if (req->ns->file)
		status = nvmet_file_flush(req);
	else
		status = nvmet_bdev_flush(req);

	if (status)
		pr_err("write protect flush failed nsid: %u\n", req->ns->nsid);
	return status;
}