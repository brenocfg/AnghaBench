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
 int /*<<< orphan*/  LCD_DMA_BURST_1 ; 
 int /*<<< orphan*/  LCD_DMA_BURST_16 ; 
 int /*<<< orphan*/  LCD_DMA_BURST_2 ; 
 int /*<<< orphan*/  LCD_DMA_BURST_4 ; 
 int /*<<< orphan*/  LCD_DMA_BURST_8 ; 
 int LCD_DMA_BURST_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCD_DMA_CTRL_REG ; 
 int lcdc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lcd_cfg_dma(int burst_size, int fifo_th)
{
	u32 reg;

	reg = lcdc_read(LCD_DMA_CTRL_REG) & 0x00000001;
	switch (burst_size) {
	case 1:
		reg |= LCD_DMA_BURST_SIZE(LCD_DMA_BURST_1);
		break;
	case 2:
		reg |= LCD_DMA_BURST_SIZE(LCD_DMA_BURST_2);
		break;
	case 4:
		reg |= LCD_DMA_BURST_SIZE(LCD_DMA_BURST_4);
		break;
	case 8:
		reg |= LCD_DMA_BURST_SIZE(LCD_DMA_BURST_8);
		break;
	case 16:
	default:
		reg |= LCD_DMA_BURST_SIZE(LCD_DMA_BURST_16);
		break;
	}

	reg |= (fifo_th << 8);

	lcdc_write(reg, LCD_DMA_CTRL_REG);

	return 0;
}