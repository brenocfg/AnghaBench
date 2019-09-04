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
typedef  int /*<<< orphan*/  u32 ;
struct msm_dma {int device_fc; int /*<<< orphan*/  chan; int /*<<< orphan*/  virt; int /*<<< orphan*/  enable_bit; int /*<<< orphan*/  dir; int /*<<< orphan*/  slave_id; int /*<<< orphan*/  src_maxburst; scalar_t__ src_addr; int /*<<< orphan*/  direction; } ;
struct TYPE_2__ {struct device* dev; } ;
struct msm_port {scalar_t__ is_uartdm; struct msm_dma rx_dma; TYPE_1__ uart; } ;
struct dma_slave_config {int device_fc; int /*<<< orphan*/  chan; int /*<<< orphan*/  virt; int /*<<< orphan*/  enable_bit; int /*<<< orphan*/  dir; int /*<<< orphan*/  slave_id; int /*<<< orphan*/  src_maxburst; scalar_t__ src_addr; int /*<<< orphan*/  direction; } ;
struct device {int /*<<< orphan*/  of_node; } ;
typedef  scalar_t__ resource_size_t ;
typedef  int /*<<< orphan*/  conf ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ UARTDM_1P4 ; 
 int /*<<< orphan*/  UARTDM_BURST_SIZE ; 
 int /*<<< orphan*/  UARTDM_DMEN_RX_BAM_ENABLE ; 
 int /*<<< orphan*/  UARTDM_DMEN_RX_DM_ENABLE ; 
 scalar_t__ UARTDM_RF ; 
 int /*<<< orphan*/  UARTDM_RX_SIZE ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_request_slave_channel_reason (struct device*,char*) ; 
 int dmaengine_slave_config (int /*<<< orphan*/ ,struct msm_dma*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct msm_dma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msm_request_rx_dma(struct msm_port *msm_port, resource_size_t base)
{
	struct device *dev = msm_port->uart.dev;
	struct dma_slave_config conf;
	struct msm_dma *dma;
	u32 crci = 0;
	int ret;

	dma = &msm_port->rx_dma;

	/* allocate DMA resources, if available */
	dma->chan = dma_request_slave_channel_reason(dev, "rx");
	if (IS_ERR(dma->chan))
		goto no_rx;

	of_property_read_u32(dev->of_node, "qcom,rx-crci", &crci);

	dma->virt = kzalloc(UARTDM_RX_SIZE, GFP_KERNEL);
	if (!dma->virt)
		goto rel_rx;

	memset(&conf, 0, sizeof(conf));
	conf.direction = DMA_DEV_TO_MEM;
	conf.device_fc = true;
	conf.src_addr = base + UARTDM_RF;
	conf.src_maxburst = UARTDM_BURST_SIZE;
	conf.slave_id = crci;

	ret = dmaengine_slave_config(dma->chan, &conf);
	if (ret)
		goto err;

	dma->dir = DMA_FROM_DEVICE;

	if (msm_port->is_uartdm < UARTDM_1P4)
		dma->enable_bit = UARTDM_DMEN_RX_DM_ENABLE;
	else
		dma->enable_bit = UARTDM_DMEN_RX_BAM_ENABLE;

	return;
err:
	kfree(dma->virt);
rel_rx:
	dma_release_channel(dma->chan);
no_rx:
	memset(dma, 0, sizeof(*dma));
}