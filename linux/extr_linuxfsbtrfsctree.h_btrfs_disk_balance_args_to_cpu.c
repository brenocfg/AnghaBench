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
struct btrfs_disk_balance_args {int /*<<< orphan*/  stripes_max; int /*<<< orphan*/  stripes_min; int /*<<< orphan*/  limit; int /*<<< orphan*/  flags; int /*<<< orphan*/  target; int /*<<< orphan*/  vend; int /*<<< orphan*/  vstart; int /*<<< orphan*/  pend; int /*<<< orphan*/  pstart; int /*<<< orphan*/  devid; int /*<<< orphan*/  usage; int /*<<< orphan*/  profiles; } ;
struct btrfs_balance_args {void* stripes_max; void* stripes_min; void* limit; void* flags; void* target; void* vend; void* vstart; void* pend; void* pstart; void* devid; void* usage; void* profiles; } ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct btrfs_balance_args*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
btrfs_disk_balance_args_to_cpu(struct btrfs_balance_args *cpu,
			       const struct btrfs_disk_balance_args *disk)
{
	memset(cpu, 0, sizeof(*cpu));

	cpu->profiles = le64_to_cpu(disk->profiles);
	cpu->usage = le64_to_cpu(disk->usage);
	cpu->devid = le64_to_cpu(disk->devid);
	cpu->pstart = le64_to_cpu(disk->pstart);
	cpu->pend = le64_to_cpu(disk->pend);
	cpu->vstart = le64_to_cpu(disk->vstart);
	cpu->vend = le64_to_cpu(disk->vend);
	cpu->target = le64_to_cpu(disk->target);
	cpu->flags = le64_to_cpu(disk->flags);
	cpu->limit = le64_to_cpu(disk->limit);
	cpu->stripes_min = le32_to_cpu(disk->stripes_min);
	cpu->stripes_max = le32_to_cpu(disk->stripes_max);
}