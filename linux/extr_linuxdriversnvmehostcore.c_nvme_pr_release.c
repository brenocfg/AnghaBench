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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct block_device {int dummy; } ;
typedef  enum pr_type { ____Placeholder_pr_type } pr_type ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_cmd_resv_release ; 
 int nvme_pr_command (struct block_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_pr_type (int) ; 

__attribute__((used)) static int nvme_pr_release(struct block_device *bdev, u64 key, enum pr_type type)
{
	u32 cdw10 = nvme_pr_type(type) << 8 | (key ? 1 << 3 : 0);
	return nvme_pr_command(bdev, cdw10, key, 0, nvme_cmd_resv_release);
}