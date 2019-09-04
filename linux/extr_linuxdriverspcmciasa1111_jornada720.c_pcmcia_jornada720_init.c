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
struct sa1111_dev {int dummy; } ;

/* Variables and functions */
 unsigned int GPIO_A0 ; 
 unsigned int GPIO_A1 ; 
 unsigned int GPIO_A2 ; 
 unsigned int GPIO_A3 ; 
 int GRER ; 
 int /*<<< orphan*/  jornada720_pcmcia_ops ; 
 int sa1111_pcmcia_add (struct sa1111_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1111_set_io (struct sa1111_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1111_set_io_dir (struct sa1111_dev*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1111_set_sleep_io (struct sa1111_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa11xx_drv_pcmcia_add_one ; 
 int /*<<< orphan*/  sa11xx_drv_pcmcia_ops (int /*<<< orphan*/ *) ; 

int pcmcia_jornada720_init(struct sa1111_dev *sadev)
{
	unsigned int pin = GPIO_A0 | GPIO_A1 | GPIO_A2 | GPIO_A3;

	/* Fixme: why messing around with SA11x0's GPIO1? */
	GRER |= 0x00000002;

	/* Set GPIO_A<3:1> to be outputs for PCMCIA/CF power controller: */
	sa1111_set_io_dir(sadev, pin, 0, 0);
	sa1111_set_io(sadev, pin, 0);
	sa1111_set_sleep_io(sadev, pin, 0);

	sa11xx_drv_pcmcia_ops(&jornada720_pcmcia_ops);
	return sa1111_pcmcia_add(sadev, &jornada720_pcmcia_ops,
				 sa11xx_drv_pcmcia_add_one);
}