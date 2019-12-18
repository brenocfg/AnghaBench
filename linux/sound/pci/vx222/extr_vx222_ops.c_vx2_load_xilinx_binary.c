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
struct firmware {unsigned char* data; unsigned int size; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTRL ; 
 int EINVAL ; 
 int /*<<< orphan*/  GPIOC ; 
 unsigned int VX_CNTRL ; 
 int VX_CNTRL_REGISTER_VALUE ; 
 unsigned int VX_GPIOC ; 
 scalar_t__ VX_TYPE_BOARD ; 
 int VX_XILINX_RESET_MASK ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ put_xilinx_data (struct vx_core*,unsigned int,int,unsigned char const) ; 
 unsigned int vx_inl (struct vx_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_outl (struct vx_core*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vx2_load_xilinx_binary(struct vx_core *chip, const struct firmware *xilinx)
{
	unsigned int i;
	unsigned int port;
	const unsigned char *image;

	/* XILINX reset (wait at least 1 millisecond between reset on and off). */
	vx_outl(chip, CNTRL, VX_CNTRL_REGISTER_VALUE | VX_XILINX_RESET_MASK);
	vx_inl(chip, CNTRL);
	msleep(10);
	vx_outl(chip, CNTRL, VX_CNTRL_REGISTER_VALUE);
	vx_inl(chip, CNTRL);
	msleep(10);

	if (chip->type == VX_TYPE_BOARD)
		port = VX_CNTRL;
	else
		port = VX_GPIOC; /* VX222 V2 and VX222_MIC_BOARD with new PLX9030 use this register */

	image = xilinx->data;
	for (i = 0; i < xilinx->size; i++, image++) {
		if (put_xilinx_data(chip, port, 8, *image) < 0)
			return -EINVAL;
		/* don't take too much time in this loop... */
		cond_resched();
	}
	put_xilinx_data(chip, port, 4, 0xff); /* end signature */

	msleep(200);

	/* test after loading (is buggy with VX222) */
	if (chip->type != VX_TYPE_BOARD) {
		/* Test if load successful: test bit 8 of register GPIOC (VX222: use CNTRL) ! */
		i = vx_inl(chip, GPIOC);
		if (i & 0x0100)
			return 0;
		dev_err(chip->card->dev,
			"xilinx test failed after load, GPIOC=0x%x\n", i);
		return -EINVAL;
	}

	return 0;
}