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
struct skl_pipe_params {int /*<<< orphan*/  s_fmt; int /*<<< orphan*/  ch; int /*<<< orphan*/  s_freq; } ;
struct skl_module_fmt {int valid_bit_depth; int bit_depth; int /*<<< orphan*/  channels; int /*<<< orphan*/  s_freq; } ;

/* Variables and functions */
 int SKL_CH_FIXUP_MASK ; 
#define  SKL_DEPTH_16BIT 128 
 int SKL_DEPTH_32BIT ; 
 int SKL_FMT_FIXUP_MASK ; 
 int SKL_RATE_FIXUP_MASK ; 
 int skl_get_bit_depth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_tplg_update_chmap (struct skl_module_fmt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skl_tplg_update_params(struct skl_module_fmt *fmt,
			struct skl_pipe_params *params, int fixup)
{
	if (fixup & SKL_RATE_FIXUP_MASK)
		fmt->s_freq = params->s_freq;
	if (fixup & SKL_CH_FIXUP_MASK) {
		fmt->channels = params->ch;
		skl_tplg_update_chmap(fmt, fmt->channels);
	}
	if (fixup & SKL_FMT_FIXUP_MASK) {
		fmt->valid_bit_depth = skl_get_bit_depth(params->s_fmt);

		/*
		 * 16 bit is 16 bit container whereas 24 bit is in 32 bit
		 * container so update bit depth accordingly
		 */
		switch (fmt->valid_bit_depth) {
		case SKL_DEPTH_16BIT:
			fmt->bit_depth = fmt->valid_bit_depth;
			break;

		default:
			fmt->bit_depth = SKL_DEPTH_32BIT;
			break;
		}
	}

}