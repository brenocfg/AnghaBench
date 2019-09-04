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
struct mvebu_mpp_ctrl_data {int dummy; } ;

/* Variables and functions */
 unsigned long CAM_GPIO_SEL ; 
 int EINVAL ; 
 unsigned long SD0_GPIO_SEL ; 
 unsigned long SD1_GPIO_SEL ; 
 unsigned long SPI_GPIO_SEL ; 
 unsigned long UART1_GPIO_SEL ; 
 int /*<<< orphan*/  mpp4_base ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dove_mpp4_ctrl_get(struct mvebu_mpp_ctrl_data *data, unsigned pid,
			      unsigned long *config)
{
	unsigned long mpp4 = readl(mpp4_base);
	unsigned long mask;

	switch (pid) {
	case 24: /* mpp_camera */
		mask = CAM_GPIO_SEL;
		break;
	case 40: /* mpp_sdio0 */
		mask = SD0_GPIO_SEL;
		break;
	case 46: /* mpp_sdio1 */
		mask = SD1_GPIO_SEL;
		break;
	case 58: /* mpp_spi0 */
		mask = SPI_GPIO_SEL;
		break;
	case 62: /* mpp_uart1 */
		mask = UART1_GPIO_SEL;
		break;
	default:
		return -EINVAL;
	}

	*config = ((mpp4 & mask) != 0);

	return 0;
}