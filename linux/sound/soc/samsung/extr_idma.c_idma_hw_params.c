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
typedef  int u32 ;
struct snd_pcm_substream {int /*<<< orphan*/  dma_buffer; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ dma_bytes; scalar_t__ dma_addr; struct idma_ctrl* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct idma_ctrl {scalar_t__ end; int /*<<< orphan*/  periodsz; int /*<<< orphan*/  period; scalar_t__ pos; scalar_t__ start; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 int AHB_DMARLD ; 
 int AHB_INTMASK ; 
 scalar_t__ I2SAHB ; 
 scalar_t__ I2SMOD ; 
 int MOD_TXS_IDMA ; 
 TYPE_1__ idma ; 
 int /*<<< orphan*/  idma_done ; 
 int /*<<< orphan*/  idma_setcallbk (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 scalar_t__ params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_period_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_periods (struct snd_pcm_hw_params*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  snd_pcm_set_runtime_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int idma_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct idma_ctrl *prtd = substream->runtime->private_data;
	u32 mod = readl(idma.regs + I2SMOD);
	u32 ahb = readl(idma.regs + I2SAHB);

	ahb |= (AHB_DMARLD | AHB_INTMASK);
	mod |= MOD_TXS_IDMA;
	writel(ahb, idma.regs + I2SAHB);
	writel(mod, idma.regs + I2SMOD);

	snd_pcm_set_runtime_buffer(substream, &substream->dma_buffer);
	runtime->dma_bytes = params_buffer_bytes(params);

	prtd->start = prtd->pos = runtime->dma_addr;
	prtd->period = params_periods(params);
	prtd->periodsz = params_period_bytes(params);
	prtd->end = runtime->dma_addr + runtime->dma_bytes;

	idma_setcallbk(substream, idma_done);

	return 0;
}