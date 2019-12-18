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
 unsigned int EIO ; 
 int /*<<< orphan*/  VENDOR_DSPIO_DSP_INIT ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 
 unsigned int dspio_send (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsp_reset(struct hda_codec *codec)
{
	unsigned int res;
	int retry = 20;

	codec_dbg(codec, "dsp_reset\n");
	do {
		res = dspio_send(codec, VENDOR_DSPIO_DSP_INIT, 0);
		retry--;
	} while (res == -EIO && retry);

	if (!retry) {
		codec_dbg(codec, "dsp_reset timeout\n");
		return -EIO;
	}

	return 0;
}