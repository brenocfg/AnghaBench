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
struct bio {scalar_t__ bi_status; struct nvmet_req* bi_private; } ;
struct TYPE_2__ {struct bio inline_bio; } ;
struct nvmet_req {TYPE_1__ b; } ;

/* Variables and functions */
 int NVME_SC_DNR ; 
 int NVME_SC_INTERNAL ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int) ; 

__attribute__((used)) static void nvmet_bio_done(struct bio *bio)
{
	struct nvmet_req *req = bio->bi_private;

	nvmet_req_complete(req,
		bio->bi_status ? NVME_SC_INTERNAL | NVME_SC_DNR : 0);

	if (bio != &req->b.inline_bio)
		bio_put(bio);
}