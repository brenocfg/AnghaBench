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
struct sa1111_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int GPIO_A0 ; 
 int GPIO_A1 ; 
 int GPIO_A2 ; 
 int GPIO_A3 ; 
 int /*<<< orphan*/  lubbock_pcmcia_ops ; 
 int /*<<< orphan*/  lubbock_set_misc_wr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa2xx_configure_sockets (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pxa2xx_drv_pcmcia_add_one ; 
 int /*<<< orphan*/  pxa2xx_drv_pcmcia_ops (int /*<<< orphan*/ *) ; 
 int sa1111_pcmcia_add (struct sa1111_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1111_set_io (struct sa1111_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1111_set_io_dir (struct sa1111_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1111_set_sleep_io (struct sa1111_dev*,int,int /*<<< orphan*/ ) ; 

int pcmcia_lubbock_init(struct sa1111_dev *sadev)
{
	/*
	 * Set GPIO_A<3:0> to be outputs for the MAX1600,
	 * and switch to standby mode.
	 */
	sa1111_set_io_dir(sadev, GPIO_A0|GPIO_A1|GPIO_A2|GPIO_A3, 0, 0);
	sa1111_set_io(sadev, GPIO_A0|GPIO_A1|GPIO_A2|GPIO_A3, 0);
	sa1111_set_sleep_io(sadev, GPIO_A0|GPIO_A1|GPIO_A2|GPIO_A3, 0);

	/* Set CF Socket 1 power to standby mode. */
	lubbock_set_misc_wr((1 << 15) | (1 << 14), 0);

	pxa2xx_drv_pcmcia_ops(&lubbock_pcmcia_ops);
	pxa2xx_configure_sockets(&sadev->dev, &lubbock_pcmcia_ops);
	return sa1111_pcmcia_add(sadev, &lubbock_pcmcia_ops,
				 pxa2xx_drv_pcmcia_add_one);
}