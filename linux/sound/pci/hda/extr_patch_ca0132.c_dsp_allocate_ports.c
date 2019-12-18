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
 int dsp_allocate_router_ports (struct hda_codec*,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int dsp_allocate_ports(struct hda_codec *codec,
			unsigned int num_chans,
			unsigned int rate_multi, unsigned int *port_map)
{
	int status;

	codec_dbg(codec, "     dsp_allocate_ports() -- begin\n");

	if ((rate_multi != 1) && (rate_multi != 2) && (rate_multi != 4)) {
		codec_dbg(codec, "bad rate multiple\n");
		return -EINVAL;
	}

	status = dsp_allocate_router_ports(codec, num_chans,
					   rate_multi, 0, port_map);

	codec_dbg(codec, "     dsp_allocate_ports() -- complete\n");

	return status;
}