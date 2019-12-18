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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 
 int dsp_allocate_ports (struct hda_codec*,unsigned int,unsigned int,unsigned int*) ; 
 int get_hdafmt_chs (unsigned short const) ; 
 int get_hdafmt_rate (unsigned short const) ; 

__attribute__((used)) static int dsp_allocate_ports_format(struct hda_codec *codec,
			const unsigned short fmt,
			unsigned int *port_map)
{
	int status;
	unsigned int num_chans;

	unsigned int sample_rate_div = ((get_hdafmt_rate(fmt) >> 0) & 3) + 1;
	unsigned int sample_rate_mul = ((get_hdafmt_rate(fmt) >> 3) & 3) + 1;
	unsigned int rate_multi = sample_rate_mul / sample_rate_div;

	if ((rate_multi != 1) && (rate_multi != 2) && (rate_multi != 4)) {
		codec_dbg(codec, "bad rate multiple\n");
		return -EINVAL;
	}

	num_chans = get_hdafmt_chs(fmt) + 1;

	status = dsp_allocate_ports(codec, num_chans, rate_multi, port_map);

	return status;
}