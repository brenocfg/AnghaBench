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
struct skl_module_fmt {int /*<<< orphan*/  interleaving_style; int /*<<< orphan*/  ch_map; int /*<<< orphan*/  sample_type; int /*<<< orphan*/  ch_cfg; int /*<<< orphan*/  valid_bit_depth; int /*<<< orphan*/  bit_depth; int /*<<< orphan*/  s_freq; int /*<<< orphan*/  channels; } ;
struct skl_audio_data_format {int /*<<< orphan*/  interleaving; int /*<<< orphan*/  channel_map; int /*<<< orphan*/  sample_type; int /*<<< orphan*/  ch_cfg; int /*<<< orphan*/  valid_bit_depth; int /*<<< orphan*/  bit_depth; int /*<<< orphan*/  s_freq; int /*<<< orphan*/  number_of_channels; } ;

/* Variables and functions */

__attribute__((used)) static void fill_pin_params(struct skl_audio_data_format *pin_fmt,
				struct skl_module_fmt *format)
{
	pin_fmt->number_of_channels = format->channels;
	pin_fmt->s_freq = format->s_freq;
	pin_fmt->bit_depth = format->bit_depth;
	pin_fmt->valid_bit_depth = format->valid_bit_depth;
	pin_fmt->ch_cfg = format->ch_cfg;
	pin_fmt->sample_type = format->sample_type;
	pin_fmt->channel_map = format->ch_map;
	pin_fmt->interleaving = format->interleaving_style;
}