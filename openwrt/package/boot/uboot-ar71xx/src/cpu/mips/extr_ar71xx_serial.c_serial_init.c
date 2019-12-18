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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ AR71XX_GPIO_BASE ; 
 int /*<<< orphan*/  AR71XX_GPIO_FUNC_UART_EN ; 
 int /*<<< orphan*/  AR91XX_GPIO_FUNC_UART_EN ; 
 int CONFIG_BAUDRATE ; 
 scalar_t__ GPIO_REG_FUNC ; 
 int /*<<< orphan*/  KSEG1ADDR (scalar_t__) ; 
 int /*<<< orphan*/  OFS_DATA_FORMAT ; 
 int /*<<< orphan*/  OFS_DIVISOR_LSB ; 
 int /*<<< orphan*/  OFS_DIVISOR_MSB ; 
 int /*<<< orphan*/  OFS_INTR_ENABLE ; 
 int /*<<< orphan*/  OFS_LINE_CONTROL ; 
 int /*<<< orphan*/  UART16550_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar71xx_sys_frequency (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int serial_init(void)
{
    u32 div;
    u32 ahb_freq = 100000000;

    ar71xx_sys_frequency  (0, 0, &ahb_freq);  
    div  = ahb_freq/(16 * CONFIG_BAUDRATE);  

	// enable uart pins
#ifndef CONFIG_AR91XX
    writel(AR71XX_GPIO_FUNC_UART_EN, KSEG1ADDR(AR71XX_GPIO_BASE + GPIO_REG_FUNC));
#else
	writel(AR91XX_GPIO_FUNC_UART_EN, KSEG1ADDR(AR71XX_GPIO_BASE + GPIO_REG_FUNC));
#endif

    /* set DIAB bit */
    UART16550_WRITE(OFS_LINE_CONTROL, 0x80);

    /* set divisor */
    UART16550_WRITE(OFS_DIVISOR_LSB, (div & 0xff));
    UART16550_WRITE(OFS_DIVISOR_MSB, ((div >> 8) & 0xff));

    /* clear DIAB bit*/ 
    UART16550_WRITE(OFS_LINE_CONTROL, 0x00);

    /* set data format */
    UART16550_WRITE(OFS_DATA_FORMAT, 0x3);

    UART16550_WRITE(OFS_INTR_ENABLE, 0);

	return 0;
}