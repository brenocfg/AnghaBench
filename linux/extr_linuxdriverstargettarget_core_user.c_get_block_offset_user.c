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
struct tcmu_dev {size_t data_off; } ;

/* Variables and functions */
 int DATA_BLOCK_SIZE ; 

__attribute__((used)) static inline size_t get_block_offset_user(struct tcmu_dev *dev,
		int dbi, int remaining)
{
	return dev->data_off + dbi * DATA_BLOCK_SIZE +
		DATA_BLOCK_SIZE - remaining;
}