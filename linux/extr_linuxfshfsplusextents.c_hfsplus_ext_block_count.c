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
typedef  int u32 ;
struct hfsplus_extent {int /*<<< orphan*/  block_count; } ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hfsplus_ext_block_count(struct hfsplus_extent *ext)
{
	int i;
	u32 count = 0;

	for (i = 0; i < 8; ext++, i++)
		count += be32_to_cpu(ext->block_count);
	return count;
}