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
typedef  int /*<<< orphan*/  u16 ;
struct nvmet_req {TYPE_1__* sq; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nvmet_req_complete (struct nvmet_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_ref_put (int /*<<< orphan*/ *) ; 

void nvmet_req_complete(struct nvmet_req *req, u16 status)
{
	__nvmet_req_complete(req, status);
	percpu_ref_put(&req->sq->ref);
}