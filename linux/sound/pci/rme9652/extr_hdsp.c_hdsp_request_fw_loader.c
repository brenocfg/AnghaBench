#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hdsp {int io_type; int firmware_rev; int state; TYPE_2__* card; struct firmware const* firmware; TYPE_1__* pci; } ;
struct firmware {scalar_t__ size; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  Digiface 130 
 int EINVAL ; 
 int ENOENT ; 
 int H9632 ; 
 int H9652 ; 
 scalar_t__ HDSP_FIRMWARE_SIZE ; 
 int HDSP_FirmwareCached ; 
 int HDSP_InitializationComplete ; 
#define  Multiface 129 
#define  RPM 128 
 int Undefined ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int hdsp_get_iobox_version (struct hdsp*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 scalar_t__ request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 
 int snd_hdsp_create_alsa_devices (TYPE_2__*,struct hdsp*) ; 
 int snd_hdsp_create_hwdep (TYPE_2__*,struct hdsp*) ; 
 int snd_hdsp_enable_io (struct hdsp*) ; 
 int /*<<< orphan*/  snd_hdsp_initialize_channels (struct hdsp*) ; 
 int /*<<< orphan*/  snd_hdsp_initialize_midi_flush (struct hdsp*) ; 
 int snd_hdsp_load_firmware_from_cache (struct hdsp*) ; 

__attribute__((used)) static int hdsp_request_fw_loader(struct hdsp *hdsp)
{
	const char *fwfile;
	const struct firmware *fw;
	int err;

	if (hdsp->io_type == H9652 || hdsp->io_type == H9632)
		return 0;
	if (hdsp->io_type == Undefined) {
		if ((err = hdsp_get_iobox_version(hdsp)) < 0)
			return err;
		if (hdsp->io_type == H9652 || hdsp->io_type == H9632)
			return 0;
	}

	/* caution: max length of firmware filename is 30! */
	switch (hdsp->io_type) {
	case RPM:
		fwfile = "rpm_firmware.bin";
		break;
	case Multiface:
		if (hdsp->firmware_rev == 0xa)
			fwfile = "multiface_firmware.bin";
		else
			fwfile = "multiface_firmware_rev11.bin";
		break;
	case Digiface:
		if (hdsp->firmware_rev == 0xa)
			fwfile = "digiface_firmware.bin";
		else
			fwfile = "digiface_firmware_rev11.bin";
		break;
	default:
		dev_err(hdsp->card->dev,
			"invalid io_type %d\n", hdsp->io_type);
		return -EINVAL;
	}

	if (request_firmware(&fw, fwfile, &hdsp->pci->dev)) {
		dev_err(hdsp->card->dev,
			"cannot load firmware %s\n", fwfile);
		return -ENOENT;
	}
	if (fw->size < HDSP_FIRMWARE_SIZE) {
		dev_err(hdsp->card->dev,
			"too short firmware size %d (expected %d)\n",
			   (int)fw->size, HDSP_FIRMWARE_SIZE);
		release_firmware(fw);
		return -EINVAL;
	}

	hdsp->firmware = fw;

	hdsp->state |= HDSP_FirmwareCached;

	if ((err = snd_hdsp_load_firmware_from_cache(hdsp)) < 0)
		return err;

	if (!(hdsp->state & HDSP_InitializationComplete)) {
		if ((err = snd_hdsp_enable_io(hdsp)) < 0)
			return err;

		if ((err = snd_hdsp_create_hwdep(hdsp->card, hdsp)) < 0) {
			dev_err(hdsp->card->dev,
				"error creating hwdep device\n");
			return err;
		}
		snd_hdsp_initialize_channels(hdsp);
		snd_hdsp_initialize_midi_flush(hdsp);
		if ((err = snd_hdsp_create_alsa_devices(hdsp->card, hdsp)) < 0) {
			dev_err(hdsp->card->dev,
				"error creating alsa devices\n");
			return err;
		}
	}
	return 0;
}