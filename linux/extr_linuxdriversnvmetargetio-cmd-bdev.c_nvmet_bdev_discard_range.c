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
typedef  int u16 ;
struct nvmet_ns {int blksize_shift; int /*<<< orphan*/  bdev; } ;
struct nvme_dsm_range {int /*<<< orphan*/  nlb; int /*<<< orphan*/  slba; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NVME_SC_DNR ; 
 int NVME_SC_INTERNAL ; 
 int __blkdev_issue_discard (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bio**) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 nvmet_bdev_discard_range(struct nvmet_ns *ns,
		struct nvme_dsm_range *range, struct bio **bio)
{
	int ret;

	ret = __blkdev_issue_discard(ns->bdev,
			le64_to_cpu(range->slba) << (ns->blksize_shift - 9),
			le32_to_cpu(range->nlb) << (ns->blksize_shift - 9),
			GFP_KERNEL, 0, bio);
	if (ret && ret != -EOPNOTSUPP)
		return NVME_SC_INTERNAL | NVME_SC_DNR;
	return 0;
}