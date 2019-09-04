#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ i2s_cap_stream_cfg; scalar_t__ i2s_cfg; scalar_t__ bf_destch_ctrl; scalar_t__ bf_destch_cfg; } ;
struct cygnus_aio_port {int /*<<< orphan*/  streams_on; TYPE_2__ regs; TYPE_1__* cygaud; } ;
struct TYPE_3__ {scalar_t__ i2s_in; scalar_t__ audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BF_DST_CFGX_CAP_ENA ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAPTURE_STREAM_MASK ; 
 int /*<<< orphan*/  I2S_IN_STREAM_CFG_CAP_ENA ; 
 int /*<<< orphan*/  I2S_OUT_CFGX_CLK_ENA ; 
 int /*<<< orphan*/  I2S_OUT_CFGX_DATA_ENABLE ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void audio_ssp_in_enable(struct cygnus_aio_port *aio)
{
	u32 value;

	value = readl(aio->cygaud->audio + aio->regs.bf_destch_cfg);
	value |= BIT(BF_DST_CFGX_CAP_ENA);
	writel(value, aio->cygaud->audio + aio->regs.bf_destch_cfg);

	writel(0x1, aio->cygaud->audio + aio->regs.bf_destch_ctrl);

	value = readl(aio->cygaud->audio + aio->regs.i2s_cfg);
	value |= BIT(I2S_OUT_CFGX_CLK_ENA);
	value |= BIT(I2S_OUT_CFGX_DATA_ENABLE);
	writel(value, aio->cygaud->audio + aio->regs.i2s_cfg);

	value = readl(aio->cygaud->i2s_in + aio->regs.i2s_cap_stream_cfg);
	value |= BIT(I2S_IN_STREAM_CFG_CAP_ENA);
	writel(value, aio->cygaud->i2s_in + aio->regs.i2s_cap_stream_cfg);

	aio->streams_on |= CAPTURE_STREAM_MASK;
}