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
typedef  scalar_t__ u32 ;
struct hfsplus_extent {int /*<<< orphan*/  start_block; int /*<<< orphan*/  block_count; } ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 hfsplus_ext_find_block(struct hfsplus_extent *ext, u32 off)
{
	int i;
	u32 count;

	for (i = 0; i < 8; ext++, i++) {
		count = be32_to_cpu(ext->block_count);
		if (off < count)
			return be32_to_cpu(ext->start_block) + off;
		off -= count;
	}
	/* panic? */
	return 0;
}