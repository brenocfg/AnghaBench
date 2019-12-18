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
struct hfs_extent {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hfs_ext_block_count(struct hfs_extent *ext)
{
	int i;
	u16 count = 0;

	for (i = 0; i < 3; ext++, i++)
		count += be16_to_cpu(ext->count);
	return count;
}