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
typedef  int /*<<< orphan*/  u8 ;
struct bq24190_dev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bq24190_find_idx (int const*,int,int) ; 
 int bq24190_write_mask (struct bq24190_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq24190_set_field_val(struct bq24190_dev_info *bdi,
		u8 reg, u8 mask, u8 shift,
		const int tbl[], int tbl_size,
		int val)
{
	u8 idx;

	idx = bq24190_find_idx(tbl, tbl_size, val);

	return bq24190_write_mask(bdi, reg, mask, shift, idx);
}