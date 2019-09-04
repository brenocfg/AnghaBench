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
typedef  int uint32_t ;
struct csio_hw {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int BYTECNT_V (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int OP_V (int) ; 
 int /*<<< orphan*/  SF_ATTEMPTS ; 
 int SF_BUSY_F ; 
 int SF_CONT_V (int) ; 
 int /*<<< orphan*/  SF_DATA_A ; 
 int SF_LOCK_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SF_OP_A ; 
 int csio_hw_wait_op_done_val (struct csio_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int csio_rd_reg32 (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
csio_hw_sf1_write(struct csio_hw *hw, uint32_t byte_cnt, uint32_t cont,
		  int32_t lock, uint32_t val)
{
	if (!byte_cnt || byte_cnt > 4)
		return -EINVAL;
	if (csio_rd_reg32(hw, SF_OP_A) & SF_BUSY_F)
		return -EBUSY;

	csio_wr_reg32(hw, val, SF_DATA_A);
	csio_wr_reg32(hw, SF_CONT_V(cont) | BYTECNT_V(byte_cnt - 1) |
		      OP_V(1) | SF_LOCK_V(lock), SF_OP_A);

	return csio_hw_wait_op_done_val(hw, SF_OP_A, SF_BUSY_F, 0, SF_ATTEMPTS,
					10, NULL);
}