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
struct hda_codec {TYPE_1__* card; struct ca0132_spec* spec; } ;
struct firmware {scalar_t__ data; } ;
struct dsp_image_seg {int dummy; } ;
struct ca0132_spec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESKTOP_EFX_FILE ; 
 int /*<<< orphan*/  EFX_FILE ; 
#define  QUIRK_AE5 131 
#define  QUIRK_R3D 130 
#define  QUIRK_R3DI 129 
#define  QUIRK_SBZ 128 
 int /*<<< orphan*/  R3DI_EFX_FILE ; 
 int ca0132_quirk (struct ca0132_spec*) ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 
 int /*<<< orphan*/  codec_err (struct hda_codec*,char*) ; 
 scalar_t__ dspload_image (struct hda_codec*,struct dsp_image_seg const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int dspload_wait_loaded (struct hda_codec*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 scalar_t__ request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ca0132_download_dsp_images(struct hda_codec *codec)
{
	bool dsp_loaded = false;
	struct ca0132_spec *spec = codec->spec;
	const struct dsp_image_seg *dsp_os_image;
	const struct firmware *fw_entry = NULL;
	/*
	 * Alternate firmwares for different variants. The Recon3Di apparently
	 * can use the default firmware, but I'll leave the option in case
	 * it needs it again.
	 */
	switch (ca0132_quirk(spec)) {
	case QUIRK_SBZ:
	case QUIRK_R3D:
	case QUIRK_AE5:
		if (request_firmware(&fw_entry, DESKTOP_EFX_FILE,
					codec->card->dev) != 0)
			codec_dbg(codec, "Desktop firmware not found.");
		else
			codec_dbg(codec, "Desktop firmware selected.");
		break;
	case QUIRK_R3DI:
		if (request_firmware(&fw_entry, R3DI_EFX_FILE,
					codec->card->dev) != 0)
			codec_dbg(codec, "Recon3Di alt firmware not detected.");
		else
			codec_dbg(codec, "Recon3Di firmware selected.");
		break;
	default:
		break;
	}
	/*
	 * Use default ctefx.bin if no alt firmware is detected, or if none
	 * exists for your particular codec.
	 */
	if (!fw_entry) {
		codec_dbg(codec, "Default firmware selected.");
		if (request_firmware(&fw_entry, EFX_FILE,
					codec->card->dev) != 0)
			return false;
	}

	dsp_os_image = (struct dsp_image_seg *)(fw_entry->data);
	if (dspload_image(codec, dsp_os_image, 0, 0, true, 0)) {
		codec_err(codec, "ca0132 DSP load image failed\n");
		goto exit_download;
	}

	dsp_loaded = dspload_wait_loaded(codec);

exit_download:
	release_firmware(fw_entry);

	return dsp_loaded;
}