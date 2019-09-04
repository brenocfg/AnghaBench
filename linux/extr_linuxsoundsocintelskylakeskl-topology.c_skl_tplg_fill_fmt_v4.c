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
struct TYPE_2__ {int /*<<< orphan*/  sample_type; int /*<<< orphan*/  interleaving_style; int /*<<< orphan*/  ch_map; int /*<<< orphan*/  ch_cfg; int /*<<< orphan*/  valid_bit_depth; int /*<<< orphan*/  bit_depth; int /*<<< orphan*/  s_freq; int /*<<< orphan*/  channels; } ;
struct skl_module_pin_fmt {TYPE_1__ fmt; } ;
struct skl_dfw_v4_module_fmt {int /*<<< orphan*/  sample_type; int /*<<< orphan*/  interleaving_style; int /*<<< orphan*/  ch_map; int /*<<< orphan*/  ch_cfg; int /*<<< orphan*/  valid_bit_depth; int /*<<< orphan*/  bit_depth; int /*<<< orphan*/  freq; int /*<<< orphan*/  channels; } ;

/* Variables and functions */

__attribute__((used)) static void skl_tplg_fill_fmt_v4(struct skl_module_pin_fmt *dst_fmt,
				 struct skl_dfw_v4_module_fmt *src_fmt,
				 int pins)
{
	int i;

	for (i = 0; i < pins; i++) {
		dst_fmt[i].fmt.channels  = src_fmt[i].channels;
		dst_fmt[i].fmt.s_freq = src_fmt[i].freq;
		dst_fmt[i].fmt.bit_depth = src_fmt[i].bit_depth;
		dst_fmt[i].fmt.valid_bit_depth = src_fmt[i].valid_bit_depth;
		dst_fmt[i].fmt.ch_cfg = src_fmt[i].ch_cfg;
		dst_fmt[i].fmt.ch_map = src_fmt[i].ch_map;
		dst_fmt[i].fmt.interleaving_style =
						src_fmt[i].interleaving_style;
		dst_fmt[i].fmt.sample_type = src_fmt[i].sample_type;
	}
}