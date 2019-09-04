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
struct nvmet_req {scalar_t__ ns; TYPE_1__* sq; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvmet_put_namespace (scalar_t__) ; 
 int /*<<< orphan*/  percpu_ref_put (int /*<<< orphan*/ *) ; 

void nvmet_req_uninit(struct nvmet_req *req)
{
	percpu_ref_put(&req->sq->ref);
	if (req->ns)
		nvmet_put_namespace(req->ns);
}