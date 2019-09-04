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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct wav_fmt {scalar_t__ channels; scalar_t__ bits_per_sample; scalar_t__ samples_per_sec; } ;
struct nhlt_specific_cfg {scalar_t__ size; scalar_t__ caps; } ;
struct TYPE_2__ {struct wav_fmt fmt; } ;
struct nhlt_fmt_cfg {struct nhlt_specific_cfg config; TYPE_1__ fmt_ext; } ;
struct nhlt_fmt {int fmt_count; struct nhlt_fmt_cfg* fmt_config; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ NHLT_LINK_DMIC ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__,...) ; 

__attribute__((used)) static struct nhlt_specific_cfg *skl_get_specific_cfg(
		struct device *dev, struct nhlt_fmt *fmt,
		u8 no_ch, u32 rate, u16 bps, u8 linktype)
{
	struct nhlt_specific_cfg *sp_config;
	struct wav_fmt *wfmt;
	struct nhlt_fmt_cfg *fmt_config = fmt->fmt_config;
	int i;

	dev_dbg(dev, "Format count =%d\n", fmt->fmt_count);

	for (i = 0; i < fmt->fmt_count; i++) {
		wfmt = &fmt_config->fmt_ext.fmt;
		dev_dbg(dev, "ch=%d fmt=%d s_rate=%d\n", wfmt->channels,
			 wfmt->bits_per_sample, wfmt->samples_per_sec);
		if (wfmt->channels == no_ch && wfmt->bits_per_sample == bps) {
			/*
			 * if link type is dmic ignore rate check as the blob is
			 * generic for all rates
			 */
			sp_config = &fmt_config->config;
			if (linktype == NHLT_LINK_DMIC)
				return sp_config;

			if (wfmt->samples_per_sec == rate)
				return sp_config;
		}

		fmt_config = (struct nhlt_fmt_cfg *)(fmt_config->config.caps +
						fmt_config->config.size);
	}

	return NULL;
}