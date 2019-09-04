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
struct regmap {int dummy; } ;
struct axg_tdm_stream {unsigned int channels; unsigned long* mask; } ;

/* Variables and functions */
 int AXG_TDM_NUM_LANES ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int find_first_bit (unsigned long*,int) ; 
 int find_next_bit (unsigned long*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ regmap_get_reg_stride (struct regmap*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,unsigned int,unsigned int) ; 

int axg_tdm_formatter_set_channel_masks(struct regmap *map,
					struct axg_tdm_stream *ts,
					unsigned int offset)
{
	unsigned int val, ch = ts->channels;
	unsigned long mask;
	int i, j;

	/*
	 * Distribute the channels of the stream over the available slots
	 * of each TDM lane
	 */
	for (i = 0; i < AXG_TDM_NUM_LANES; i++) {
		val = 0;
		mask = ts->mask[i];

		for (j = find_first_bit(&mask, 32);
		     (j < 32) && ch;
		     j = find_next_bit(&mask, 32, j + 1)) {
			val |= 1 << j;
			ch -= 1;
		}

		regmap_write(map, offset, val);
		offset += regmap_get_reg_stride(map);
	}

	/*
	 * If we still have channel left at the end of the process, it means
	 * the stream has more channels than we can accommodate and we should
	 * have caught this earlier.
	 */
	if (WARN_ON(ch != 0)) {
		pr_err("channel mask error\n");
		return -EINVAL;
	}

	return 0;
}