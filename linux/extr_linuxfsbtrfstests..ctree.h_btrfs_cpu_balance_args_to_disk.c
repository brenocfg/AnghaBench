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
struct btrfs_disk_balance_args {void* stripes_max; void* stripes_min; void* limit; void* flags; void* target; void* vend; void* vstart; void* pend; void* pstart; void* devid; void* usage; void* profiles; } ;
struct btrfs_balance_args {int /*<<< orphan*/  stripes_max; int /*<<< orphan*/  stripes_min; int /*<<< orphan*/  limit; int /*<<< orphan*/  flags; int /*<<< orphan*/  target; int /*<<< orphan*/  vend; int /*<<< orphan*/  vstart; int /*<<< orphan*/  pend; int /*<<< orphan*/  pstart; int /*<<< orphan*/  devid; int /*<<< orphan*/  usage; int /*<<< orphan*/  profiles; } ;

/* Variables and functions */
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct btrfs_disk_balance_args*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
btrfs_cpu_balance_args_to_disk(struct btrfs_disk_balance_args *disk,
			       const struct btrfs_balance_args *cpu)
{
	memset(disk, 0, sizeof(*disk));

	disk->profiles = cpu_to_le64(cpu->profiles);
	disk->usage = cpu_to_le64(cpu->usage);
	disk->devid = cpu_to_le64(cpu->devid);
	disk->pstart = cpu_to_le64(cpu->pstart);
	disk->pend = cpu_to_le64(cpu->pend);
	disk->vstart = cpu_to_le64(cpu->vstart);
	disk->vend = cpu_to_le64(cpu->vend);
	disk->target = cpu_to_le64(cpu->target);
	disk->flags = cpu_to_le64(cpu->flags);
	disk->limit = cpu_to_le64(cpu->limit);
	disk->stripes_min = cpu_to_le32(cpu->stripes_min);
	disk->stripes_max = cpu_to_le32(cpu->stripes_max);
}