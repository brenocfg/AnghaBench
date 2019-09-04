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
 int /*<<< orphan*/  MEM_CONNID_DSP ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_PORT_FREE_SET ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_STATUS ; 
 int /*<<< orphan*/  WIDGET_CHIP_CTRL ; 
 int chipio_send (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsp_free_router_ports(struct hda_codec *codec)
{
	int status = 0;

	status = chipio_send(codec, VENDOR_CHIPIO_STATUS, 0);
	if (status < 0)
		return status;

	snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_PORT_FREE_SET,
			    MEM_CONNID_DSP);

	status = chipio_send(codec, VENDOR_CHIPIO_STATUS, 0);

	return status;
}