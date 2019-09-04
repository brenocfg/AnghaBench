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
struct o2hb_region {unsigned int hr_block_bytes; unsigned int hr_block_bits; scalar_t__ hr_bdev; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int o2hb_read_block_input (struct o2hb_region*,char const*,unsigned long*,unsigned int*) ; 
 struct o2hb_region* to_o2hb_region (struct config_item*) ; 

__attribute__((used)) static ssize_t o2hb_region_block_bytes_store(struct config_item *item,
					     const char *page,
					     size_t count)
{
	struct o2hb_region *reg = to_o2hb_region(item);
	int status;
	unsigned long block_bytes;
	unsigned int block_bits;

	if (reg->hr_bdev)
		return -EINVAL;

	status = o2hb_read_block_input(reg, page, &block_bytes,
				       &block_bits);
	if (status)
		return status;

	reg->hr_block_bytes = (unsigned int)block_bytes;
	reg->hr_block_bits = block_bits;

	return count;
}