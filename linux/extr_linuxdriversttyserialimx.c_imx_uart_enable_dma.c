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
struct imx_port {int dma_is_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXTL_DMA ; 
 int /*<<< orphan*/  TXTL_DMA ; 
 int /*<<< orphan*/  UCR1 ; 
 int UCR1_ATDMAEN ; 
 int UCR1_RXDMAEN ; 
 int UCR1_TXDMAEN ; 
 int imx_uart_readl (struct imx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_uart_setup_ufcr (struct imx_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_uart_writel (struct imx_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx_uart_enable_dma(struct imx_port *sport)
{
	u32 ucr1;

	imx_uart_setup_ufcr(sport, TXTL_DMA, RXTL_DMA);

	/* set UCR1 */
	ucr1 = imx_uart_readl(sport, UCR1);
	ucr1 |= UCR1_RXDMAEN | UCR1_TXDMAEN | UCR1_ATDMAEN;
	imx_uart_writel(sport, ucr1, UCR1);

	sport->dma_is_enabled = 1;
}