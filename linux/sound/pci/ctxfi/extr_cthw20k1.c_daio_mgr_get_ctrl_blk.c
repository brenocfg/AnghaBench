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
struct hw {int dummy; } ;
struct daio_mgr_ctrl_blk {void* spictl; void* spoctl; void* i2sctl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2SCTL ; 
 int /*<<< orphan*/  SPICTL ; 
 int /*<<< orphan*/  SPOCTL ; 
 void* hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 struct daio_mgr_ctrl_blk* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int daio_mgr_get_ctrl_blk(struct hw *hw, void **rblk)
{
	struct daio_mgr_ctrl_blk *blk;

	*rblk = NULL;
	blk = kzalloc(sizeof(*blk), GFP_KERNEL);
	if (!blk)
		return -ENOMEM;

	blk->i2sctl = hw_read_20kx(hw, I2SCTL);
	blk->spoctl = hw_read_20kx(hw, SPOCTL);
	blk->spictl = hw_read_20kx(hw, SPICTL);

	*rblk = blk;

	return 0;
}