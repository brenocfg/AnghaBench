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
typedef  int u8 ;
struct rt5514_dsp {int buf_base; int buf_limit; int buf_rp; int buf_size; int /*<<< orphan*/  copy_work; scalar_t__ get_size; int /*<<< orphan*/  substream; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  RT5514_BUFFER_VOICE_BASE ; 
 int /*<<< orphan*/  RT5514_BUFFER_VOICE_LIMIT ; 
 int /*<<< orphan*/  RT5514_BUFFER_VOICE_WP ; 
 int /*<<< orphan*/  rt5514_spi_burst_read (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt5514_schedule_copy(struct rt5514_dsp *rt5514_dsp)
{
	u8 buf[8];

	if (!rt5514_dsp->substream)
		return;

	rt5514_dsp->get_size = 0;

	/**
	 * The address area x1800XXXX is the register address, and it cannot
	 * support spi burst read perfectly. So we use the spi burst read
	 * individually to make sure the data correctly.
	 */
	rt5514_spi_burst_read(RT5514_BUFFER_VOICE_BASE, (u8 *)&buf,
		sizeof(buf));
	rt5514_dsp->buf_base = buf[0] | buf[1] << 8 | buf[2] << 16 |
				buf[3] << 24;

	rt5514_spi_burst_read(RT5514_BUFFER_VOICE_LIMIT, (u8 *)&buf,
		sizeof(buf));
	rt5514_dsp->buf_limit = buf[0] | buf[1] << 8 | buf[2] << 16 |
				buf[3] << 24;

	rt5514_spi_burst_read(RT5514_BUFFER_VOICE_WP, (u8 *)&buf,
		sizeof(buf));
	rt5514_dsp->buf_rp = buf[0] | buf[1] << 8 | buf[2] << 16 |
				buf[3] << 24;

	if (rt5514_dsp->buf_rp % 8)
		rt5514_dsp->buf_rp = (rt5514_dsp->buf_rp / 8) * 8;

	rt5514_dsp->buf_size = rt5514_dsp->buf_limit - rt5514_dsp->buf_base;

	if (rt5514_dsp->buf_base && rt5514_dsp->buf_limit &&
		rt5514_dsp->buf_rp && rt5514_dsp->buf_size)
		schedule_delayed_work(&rt5514_dsp->copy_work, 0);
}