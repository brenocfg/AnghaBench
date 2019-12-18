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
 int /*<<< orphan*/  NVIDIA_AFG_NID ; 
 int /*<<< orphan*/  NVIDIA_GET_SCRATCH0 ; 
 unsigned int NVIDIA_SCRATCH_TRIGGER ; 
 unsigned int NVIDIA_SCRATCH_VALID ; 
 int /*<<< orphan*/  NVIDIA_SET_SCRATCH0_BYTE0 ; 
 int /*<<< orphan*/  NVIDIA_SET_SCRATCH0_BYTE1 ; 
 int /*<<< orphan*/  NVIDIA_SET_SCRATCH0_BYTE2 ; 
 int /*<<< orphan*/  NVIDIA_SET_SCRATCH0_BYTE3 ; 
 unsigned int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void tegra_hdmi_set_format(struct hda_codec *codec, unsigned int format)
{
	unsigned int value;

	/* bits [31:30] contain the trigger and valid bits */
	value = snd_hda_codec_read(codec, NVIDIA_AFG_NID, 0,
				   NVIDIA_GET_SCRATCH0, 0);
	value = (value >> 24) & 0xff;

	/* bits [15:0] are used to store the HDA format */
	snd_hda_codec_write(codec, NVIDIA_AFG_NID, 0,
			    NVIDIA_SET_SCRATCH0_BYTE0,
			    (format >> 0) & 0xff);
	snd_hda_codec_write(codec, NVIDIA_AFG_NID, 0,
			    NVIDIA_SET_SCRATCH0_BYTE1,
			    (format >> 8) & 0xff);

	/* bits [16:24] are unused */
	snd_hda_codec_write(codec, NVIDIA_AFG_NID, 0,
			    NVIDIA_SET_SCRATCH0_BYTE2, 0);

	/*
	 * Bit 30 signals that the data is valid and hence that HDMI audio can
	 * be enabled.
	 */
	if (format == 0)
		value &= ~NVIDIA_SCRATCH_VALID;
	else
		value |= NVIDIA_SCRATCH_VALID;

	/*
	 * Whenever the trigger bit is toggled, an interrupt is raised in the
	 * HDMI codec. The HDMI driver will use that as trigger to update its
	 * configuration.
	 */
	value ^= NVIDIA_SCRATCH_TRIGGER;

	snd_hda_codec_write(codec, NVIDIA_AFG_NID, 0,
			    NVIDIA_SET_SCRATCH0_BYTE3, value);
}