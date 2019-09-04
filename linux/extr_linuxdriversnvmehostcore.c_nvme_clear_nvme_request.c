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
struct request {int rq_flags; } ;
struct TYPE_2__ {scalar_t__ flags; scalar_t__ retries; } ;

/* Variables and functions */
 int RQF_DONTPREP ; 
 TYPE_1__* nvme_req (struct request*) ; 

__attribute__((used)) static inline void nvme_clear_nvme_request(struct request *req)
{
	if (!(req->rq_flags & RQF_DONTPREP)) {
		nvme_req(req)->retries = 0;
		nvme_req(req)->flags = 0;
		req->rq_flags |= RQF_DONTPREP;
	}
}