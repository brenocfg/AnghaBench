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
struct skl_module_fmt {int channels; int s_freq; int bit_depth; int valid_bit_depth; int ch_cfg; int interleaving_style; int sample_type; int ch_map; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SKL_TKN_U32_FMT_BIT_DEPTH 135 
#define  SKL_TKN_U32_FMT_CH 134 
#define  SKL_TKN_U32_FMT_CH_CONFIG 133 
#define  SKL_TKN_U32_FMT_CH_MAP 132 
#define  SKL_TKN_U32_FMT_FREQ 131 
#define  SKL_TKN_U32_FMT_INTERLEAVE 130 
#define  SKL_TKN_U32_FMT_SAMPLE_SIZE 129 
#define  SKL_TKN_U32_FMT_SAMPLE_TYPE 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 

__attribute__((used)) static int skl_tplg_fill_fmt(struct device *dev,
		struct skl_module_fmt *dst_fmt,
		u32 tkn, u32 value)
{
	switch (tkn) {
	case SKL_TKN_U32_FMT_CH:
		dst_fmt->channels  = value;
		break;

	case SKL_TKN_U32_FMT_FREQ:
		dst_fmt->s_freq = value;
		break;

	case SKL_TKN_U32_FMT_BIT_DEPTH:
		dst_fmt->bit_depth = value;
		break;

	case SKL_TKN_U32_FMT_SAMPLE_SIZE:
		dst_fmt->valid_bit_depth = value;
		break;

	case SKL_TKN_U32_FMT_CH_CONFIG:
		dst_fmt->ch_cfg = value;
		break;

	case SKL_TKN_U32_FMT_INTERLEAVE:
		dst_fmt->interleaving_style = value;
		break;

	case SKL_TKN_U32_FMT_SAMPLE_TYPE:
		dst_fmt->sample_type = value;
		break;

	case SKL_TKN_U32_FMT_CH_MAP:
		dst_fmt->ch_map = value;
		break;

	default:
		dev_err(dev, "Invalid token %d\n", tkn);
		return -EINVAL;
	}

	return 0;
}