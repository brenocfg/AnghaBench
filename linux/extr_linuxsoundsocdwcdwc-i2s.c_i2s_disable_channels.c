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
 int /*<<< orphan*/  RER (scalar_t__) ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  TER (scalar_t__) ; 
 int /*<<< orphan*/  i2s_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void i2s_disable_channels(struct dw_i2s_dev *dev, u32 stream)
{
	u32 i = 0;

	if (stream == SNDRV_PCM_STREAM_PLAYBACK) {
		for (i = 0; i < 4; i++)
			i2s_write_reg(dev->i2s_base, TER(i), 0);
	} else {
		for (i = 0; i < 4; i++)
			i2s_write_reg(dev->i2s_base, RER(i), 0);
	}
}