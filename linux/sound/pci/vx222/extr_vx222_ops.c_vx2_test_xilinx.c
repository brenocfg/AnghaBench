#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vx_core {scalar_t__ type; TYPE_1__* card; } ;
struct snd_vx222 {int regCDSP; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDSP ; 
 int ENODEV ; 
 int /*<<< orphan*/  ISR ; 
 int /*<<< orphan*/  STATUS ; 
 int VX_CDSP_TEST0_MASK ; 
 int VX_CDSP_TEST1_MASK ; 
 unsigned int VX_STATUS_VAL_TEST0_MASK ; 
 unsigned int VX_STATUS_VAL_TEST1_MASK ; 
 scalar_t__ VX_TYPE_BOARD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct snd_vx222* to_vx222 (struct vx_core*) ; 
 unsigned int vx_inl (struct snd_vx222*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_outl (struct snd_vx222*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vx2_test_xilinx(struct vx_core *_chip)
{
	struct snd_vx222 *chip = to_vx222(_chip);
	unsigned int data;

	dev_dbg(_chip->card->dev, "testing xilinx...\n");
	/* This test uses several write/read sequences on TEST0 and TEST1 bits
	 * to figure out whever or not the xilinx was correctly loaded
	 */

	/* We write 1 on CDSP.TEST0. We should get 0 on STATUS.TEST0. */
	vx_outl(chip, CDSP, chip->regCDSP | VX_CDSP_TEST0_MASK);
	vx_inl(chip, ISR);
	data = vx_inl(chip, STATUS);
	if ((data & VX_STATUS_VAL_TEST0_MASK) == VX_STATUS_VAL_TEST0_MASK) {
		dev_dbg(_chip->card->dev, "bad!\n");
		return -ENODEV;
	}

	/* We write 0 on CDSP.TEST0. We should get 1 on STATUS.TEST0. */
	vx_outl(chip, CDSP, chip->regCDSP & ~VX_CDSP_TEST0_MASK);
	vx_inl(chip, ISR);
	data = vx_inl(chip, STATUS);
	if (! (data & VX_STATUS_VAL_TEST0_MASK)) {
		dev_dbg(_chip->card->dev, "bad! #2\n");
		return -ENODEV;
	}

	if (_chip->type == VX_TYPE_BOARD) {
		/* not implemented on VX_2_BOARDS */
		/* We write 1 on CDSP.TEST1. We should get 0 on STATUS.TEST1. */
		vx_outl(chip, CDSP, chip->regCDSP | VX_CDSP_TEST1_MASK);
		vx_inl(chip, ISR);
		data = vx_inl(chip, STATUS);
		if ((data & VX_STATUS_VAL_TEST1_MASK) == VX_STATUS_VAL_TEST1_MASK) {
			dev_dbg(_chip->card->dev, "bad! #3\n");
			return -ENODEV;
		}

		/* We write 0 on CDSP.TEST1. We should get 1 on STATUS.TEST1. */
		vx_outl(chip, CDSP, chip->regCDSP & ~VX_CDSP_TEST1_MASK);
		vx_inl(chip, ISR);
		data = vx_inl(chip, STATUS);
		if (! (data & VX_STATUS_VAL_TEST1_MASK)) {
			dev_dbg(_chip->card->dev, "bad! #4\n");
			return -ENODEV;
		}
	}
	dev_dbg(_chip->card->dev, "ok, xilinx fine.\n");
	return 0;
}