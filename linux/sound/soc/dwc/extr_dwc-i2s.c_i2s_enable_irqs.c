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
typedef  scalar_t__ u32 ;
struct dw_i2s_dev {int /*<<< orphan*/  i2s_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMR (scalar_t__) ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 scalar_t__ i2s_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2s_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void i2s_enable_irqs(struct dw_i2s_dev *dev, u32 stream,
				   int chan_nr)
{
	u32 i, irq;

	if (stream == SNDRV_PCM_STREAM_PLAYBACK) {
		for (i = 0; i < (chan_nr / 2); i++) {
			irq = i2s_read_reg(dev->i2s_base, IMR(i));
			i2s_write_reg(dev->i2s_base, IMR(i), irq & ~0x30);
		}
	} else {
		for (i = 0; i < (chan_nr / 2); i++) {
			irq = i2s_read_reg(dev->i2s_base, IMR(i));
			i2s_write_reg(dev->i2s_base, IMR(i), irq & ~0x03);
		}
	}
}