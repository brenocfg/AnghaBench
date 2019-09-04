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
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 
 int dsp_free_router_ports (struct hda_codec*) ; 

__attribute__((used)) static int dsp_free_ports(struct hda_codec *codec)
{
	int status;

	codec_dbg(codec, "     dsp_free_ports() -- begin\n");

	status = dsp_free_router_ports(codec);
	if (status < 0) {
		codec_dbg(codec, "free router ports fail\n");
		return status;
	}
	codec_dbg(codec, "     dsp_free_ports() -- complete\n");

	return status;
}