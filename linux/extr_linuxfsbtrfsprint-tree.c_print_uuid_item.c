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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  subvol_id ;
struct extent_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (scalar_t__,int) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long long) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned long) ; 
 int /*<<< orphan*/  read_extent_buffer (struct extent_buffer*,int /*<<< orphan*/ *,unsigned long,int) ; 

__attribute__((used)) static void print_uuid_item(struct extent_buffer *l, unsigned long offset,
			    u32 item_size)
{
	if (!IS_ALIGNED(item_size, sizeof(u64))) {
		pr_warn("BTRFS: uuid item with illegal size %lu!\n",
			(unsigned long)item_size);
		return;
	}
	while (item_size) {
		__le64 subvol_id;

		read_extent_buffer(l, &subvol_id, offset, sizeof(subvol_id));
		pr_info("\t\tsubvol_id %llu\n",
		       (unsigned long long)le64_to_cpu(subvol_id));
		item_size -= sizeof(u64);
		offset += sizeof(u64);
	}
}