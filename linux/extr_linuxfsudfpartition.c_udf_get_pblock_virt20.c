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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  udf_get_pblock_virt15 (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

inline uint32_t udf_get_pblock_virt20(struct super_block *sb, uint32_t block,
				      uint16_t partition, uint32_t offset)
{
	return udf_get_pblock_virt15(sb, block, partition, offset);
}