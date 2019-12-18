#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct snd_soc_dai_driver {int dummy; } ;
struct resource {scalar_t__ start; } ;
struct TYPE_7__ {size_t fifo_size; int maxburst; void* addr_width; scalar_t__ addr; } ;
struct TYPE_8__ {TYPE_3__ dt; } ;
struct TYPE_5__ {size_t fifo_size; int maxburst; void* addr_width; scalar_t__ addr; } ;
struct TYPE_6__ {TYPE_1__ dt; } ;
struct dw_i2s_dev {TYPE_4__ capture_dma_data; int /*<<< orphan*/  capability; TYPE_2__ play_dma_data; int /*<<< orphan*/  i2s_base; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (void**) ; 
 size_t COMP1_APB_DATA_WIDTH (size_t) ; 
 int COMP1_FIFO_DEPTH_GLOBAL (size_t) ; 
 scalar_t__ COMP1_RX_ENABLED (size_t) ; 
 scalar_t__ COMP1_TX_ENABLED (size_t) ; 
 size_t COMP1_TX_WORDSIZE_0 (size_t) ; 
 size_t COMP2_RX_WORDSIZE_0 (size_t) ; 
 int /*<<< orphan*/  DWC_I2S_PLAY ; 
 int /*<<< orphan*/  DWC_I2S_RECORD ; 
 int EINVAL ; 
 int /*<<< orphan*/  I2S_COMP_PARAM_1 ; 
 int /*<<< orphan*/  I2S_COMP_PARAM_2 ; 
 scalar_t__ I2S_RXDMA ; 
 scalar_t__ I2S_TXDMA ; 
 int /*<<< orphan*/  SNDRV_PCM_RATE_8000_192000 ; 
 scalar_t__ WARN_ON (int) ; 
 void** bus_widths ; 
 int dw_configure_dai (struct dw_i2s_dev*,struct snd_soc_dai_driver*,int /*<<< orphan*/ ) ; 
 size_t* fifo_width ; 
 size_t i2s_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_configure_dai_by_dt(struct dw_i2s_dev *dev,
				   struct snd_soc_dai_driver *dw_i2s_dai,
				   struct resource *res)
{
	u32 comp1 = i2s_read_reg(dev->i2s_base, I2S_COMP_PARAM_1);
	u32 comp2 = i2s_read_reg(dev->i2s_base, I2S_COMP_PARAM_2);
	u32 fifo_depth = 1 << (1 + COMP1_FIFO_DEPTH_GLOBAL(comp1));
	u32 idx = COMP1_APB_DATA_WIDTH(comp1);
	u32 idx2;
	int ret;

	if (WARN_ON(idx >= ARRAY_SIZE(bus_widths)))
		return -EINVAL;

	ret = dw_configure_dai(dev, dw_i2s_dai, SNDRV_PCM_RATE_8000_192000);
	if (ret < 0)
		return ret;

	if (COMP1_TX_ENABLED(comp1)) {
		idx2 = COMP1_TX_WORDSIZE_0(comp1);

		dev->capability |= DWC_I2S_PLAY;
		dev->play_dma_data.dt.addr = res->start + I2S_TXDMA;
		dev->play_dma_data.dt.addr_width = bus_widths[idx];
		dev->play_dma_data.dt.fifo_size = fifo_depth *
			(fifo_width[idx2]) >> 8;
		dev->play_dma_data.dt.maxburst = 16;
	}
	if (COMP1_RX_ENABLED(comp1)) {
		idx2 = COMP2_RX_WORDSIZE_0(comp2);

		dev->capability |= DWC_I2S_RECORD;
		dev->capture_dma_data.dt.addr = res->start + I2S_RXDMA;
		dev->capture_dma_data.dt.addr_width = bus_widths[idx];
		dev->capture_dma_data.dt.fifo_size = fifo_depth *
			(fifo_width[idx2] >> 8);
		dev->capture_dma_data.dt.maxburst = 16;
	}

	return 0;

}