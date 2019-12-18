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
typedef  int u16 ;
struct i2s_dev_data {scalar_t__ capture_stream; scalar_t__ acp3x_base; scalar_t__ play_stream; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_RX_THRESHOLD ; 
 int /*<<< orphan*/  BT_TX_THRESHOLD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ mmACP_EXTERNAL_INTR_STAT ; 
 int rv_readl (scalar_t__) ; 
 int /*<<< orphan*/  rv_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 

__attribute__((used)) static irqreturn_t i2s_irq_handler(int irq, void *dev_id)
{
	u16 play_flag, cap_flag;
	u32 val;
	struct i2s_dev_data *rv_i2s_data = dev_id;

	if (!rv_i2s_data)
		return IRQ_NONE;

	play_flag = 0;
	cap_flag = 0;
	val = rv_readl(rv_i2s_data->acp3x_base + mmACP_EXTERNAL_INTR_STAT);
	if ((val & BIT(BT_TX_THRESHOLD)) && rv_i2s_data->play_stream) {
		rv_writel(BIT(BT_TX_THRESHOLD), rv_i2s_data->acp3x_base +
			  mmACP_EXTERNAL_INTR_STAT);
		snd_pcm_period_elapsed(rv_i2s_data->play_stream);
		play_flag = 1;
	}

	if ((val & BIT(BT_RX_THRESHOLD)) && rv_i2s_data->capture_stream) {
		rv_writel(BIT(BT_RX_THRESHOLD), rv_i2s_data->acp3x_base +
			  mmACP_EXTERNAL_INTR_STAT);
		snd_pcm_period_elapsed(rv_i2s_data->capture_stream);
		cap_flag = 1;
	}

	if (play_flag | cap_flag)
		return IRQ_HANDLED;
	else
		return IRQ_NONE;
}