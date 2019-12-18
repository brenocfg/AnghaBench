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
struct btrfs_key {int /*<<< orphan*/  objectid; int /*<<< orphan*/  type; int /*<<< orphan*/  offset; } ;
struct btrfs_disk_key {void* objectid; int /*<<< orphan*/  type; void* offset; } ;

/* Variables and functions */
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void btrfs_cpu_key_to_disk(struct btrfs_disk_key *disk,
					 const struct btrfs_key *cpu)
{
	disk->offset = cpu_to_le64(cpu->offset);
	disk->type = cpu->type;
	disk->objectid = cpu_to_le64(cpu->objectid);
}