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
struct da8xx_fb_par {int which_dma_channel_done; int dma_start; int dma_end; int vsync_flag; int /*<<< orphan*/  vsync_wait; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DA8XX_FRAME_NOWAIT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  LCD_DMA_FRM_BUF_BASE_ADDR_0_REG ; 
 int /*<<< orphan*/  LCD_DMA_FRM_BUF_BASE_ADDR_1_REG ; 
 int /*<<< orphan*/  LCD_DMA_FRM_BUF_CEILING_ADDR_0_REG ; 
 int /*<<< orphan*/  LCD_DMA_FRM_BUF_CEILING_ADDR_1_REG ; 
 int LCD_END_OF_FRAME0 ; 
 int LCD_END_OF_FRAME1 ; 
 int /*<<< orphan*/  LCD_END_OF_INT_IND_REG ; 
 int LCD_FIFO_UNDERFLOW ; 
 int /*<<< orphan*/  LCD_INT_ENABLE_CLR_REG ; 
 int /*<<< orphan*/  LCD_MASKED_STAT_REG ; 
 int LCD_PL_LOAD_DONE ; 
 int LCD_SYNC_LOST ; 
 int LCD_V2_PL_INT_ENA ; 
 int /*<<< orphan*/  LOAD_DATA ; 
 int frame_done_flag ; 
 int /*<<< orphan*/  frame_done_wq ; 
 int /*<<< orphan*/  lcd_blit (int /*<<< orphan*/ ,struct da8xx_fb_par*) ; 
 int /*<<< orphan*/  lcd_disable_raster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_enable_raster () ; 
 int lcdc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t lcdc_irq_handler_rev02(int irq, void *arg)
{
	struct da8xx_fb_par *par = arg;
	u32 stat = lcdc_read(LCD_MASKED_STAT_REG);

	if ((stat & LCD_SYNC_LOST) && (stat & LCD_FIFO_UNDERFLOW)) {
		lcd_disable_raster(DA8XX_FRAME_NOWAIT);
		lcdc_write(stat, LCD_MASKED_STAT_REG);
		lcd_enable_raster();
	} else if (stat & LCD_PL_LOAD_DONE) {
		/*
		 * Must disable raster before changing state of any control bit.
		 * And also must be disabled before clearing the PL loading
		 * interrupt via the following write to the status register. If
		 * this is done after then one gets multiple PL done interrupts.
		 */
		lcd_disable_raster(DA8XX_FRAME_NOWAIT);

		lcdc_write(stat, LCD_MASKED_STAT_REG);

		/* Disable PL completion interrupt */
		lcdc_write(LCD_V2_PL_INT_ENA, LCD_INT_ENABLE_CLR_REG);

		/* Setup and start data loading mode */
		lcd_blit(LOAD_DATA, par);
	} else {
		lcdc_write(stat, LCD_MASKED_STAT_REG);

		if (stat & LCD_END_OF_FRAME0) {
			par->which_dma_channel_done = 0;
			lcdc_write(par->dma_start,
				   LCD_DMA_FRM_BUF_BASE_ADDR_0_REG);
			lcdc_write(par->dma_end,
				   LCD_DMA_FRM_BUF_CEILING_ADDR_0_REG);
			par->vsync_flag = 1;
			wake_up_interruptible(&par->vsync_wait);
		}

		if (stat & LCD_END_OF_FRAME1) {
			par->which_dma_channel_done = 1;
			lcdc_write(par->dma_start,
				   LCD_DMA_FRM_BUF_BASE_ADDR_1_REG);
			lcdc_write(par->dma_end,
				   LCD_DMA_FRM_BUF_CEILING_ADDR_1_REG);
			par->vsync_flag = 1;
			wake_up_interruptible(&par->vsync_wait);
		}

		/* Set only when controller is disabled and at the end of
		 * active frame
		 */
		if (stat & BIT(0)) {
			frame_done_flag = 1;
			wake_up_interruptible(&frame_done_wq);
		}
	}

	lcdc_write(0, LCD_END_OF_INT_IND_REG);
	return IRQ_HANDLED;
}