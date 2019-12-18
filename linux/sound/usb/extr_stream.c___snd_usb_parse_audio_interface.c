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
struct usb_interface_descriptor {int bInterfaceProtocol; scalar_t__ bInterfaceClass; scalar_t__ bInterfaceSubClass; int bNumEndpoints; int bAlternateSetting; } ;
struct usb_interface {int num_altsetting; struct usb_host_interface* altsetting; } ;
struct usb_host_interface {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct snd_usb_power_domain {int dummy; } ;
struct snd_usb_audio {scalar_t__ usb_id; struct usb_device* dev; } ;
struct audioformat {int altsetting; int channels; int maxpacksize; scalar_t__ fmt_type; int endpoint; int /*<<< orphan*/  rate_max; int /*<<< orphan*/  formats; } ;
struct TYPE_2__ {int bmAttributes; int bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct audioformat*) ; 
 int PTR_ERR (struct audioformat*) ; 
 int /*<<< orphan*/  SNDRV_PCM_FMTBIT_S16_LE ; 
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 scalar_t__ UAC_FORMAT_TYPE_I ; 
#define  UAC_VERSION_1 130 
#define  UAC_VERSION_2 129 
#define  UAC_VERSION_3 128 
 scalar_t__ USB_CLASS_AUDIO ; 
 scalar_t__ USB_CLASS_VENDOR_SPEC ; 
 int USB_DIR_IN ; 
 int USB_ENDPOINT_XFERTYPE_MASK ; 
 int USB_ENDPOINT_XFER_ISOC ; 
 scalar_t__ USB_ID (int,int) ; 
 int USB_ID_VENDOR (scalar_t__) ; 
 scalar_t__ USB_SUBCLASS_AUDIOSTREAMING ; 
 scalar_t__ USB_SUBCLASS_VENDOR_SPEC ; 
 int /*<<< orphan*/  audioformat_free (struct audioformat*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 
 TYPE_1__* get_endpoint (struct usb_host_interface*,int /*<<< orphan*/ ) ; 
 struct usb_interface_descriptor* get_iface_desc (struct usb_host_interface*) ; 
 int /*<<< orphan*/  kfree (struct snd_usb_power_domain*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int snd_usb_add_audio_stream (struct snd_usb_audio*,int,struct audioformat*) ; 
 int snd_usb_add_audio_stream_v3 (struct snd_usb_audio*,int,struct audioformat*,struct snd_usb_power_domain*) ; 
 scalar_t__ snd_usb_apply_interface_quirk (struct snd_usb_audio*,int,int) ; 
 struct audioformat* snd_usb_get_audioformat_uac12 (struct snd_usb_audio*,struct usb_host_interface*,int,int,int,int,int,int) ; 
 struct audioformat* snd_usb_get_audioformat_uac3 (struct snd_usb_audio*,struct usb_host_interface*,struct snd_usb_power_domain**,int,int,int,int) ; 
 int /*<<< orphan*/  snd_usb_init_pitch (struct snd_usb_audio*,int,struct usb_host_interface*,struct audioformat*) ; 
 int /*<<< orphan*/  snd_usb_init_sample_rate (struct snd_usb_audio*,int,struct usb_host_interface*,struct audioformat*,int /*<<< orphan*/ ) ; 
 struct usb_interface* usb_ifnum_to_if (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_set_interface (struct usb_device*,int,int) ; 

__attribute__((used)) static int __snd_usb_parse_audio_interface(struct snd_usb_audio *chip,
					   int iface_no,
					   bool *has_non_pcm, bool non_pcm)
{
	struct usb_device *dev;
	struct usb_interface *iface;
	struct usb_host_interface *alts;
	struct usb_interface_descriptor *altsd;
	int i, altno, err, stream;
	struct audioformat *fp = NULL;
	struct snd_usb_power_domain *pd = NULL;
	int num, protocol;

	dev = chip->dev;

	/* parse the interface's altsettings */
	iface = usb_ifnum_to_if(dev, iface_no);

	num = iface->num_altsetting;

	/*
	 * Dallas DS4201 workaround: It presents 5 altsettings, but the last
	 * one misses syncpipe, and does not produce any sound.
	 */
	if (chip->usb_id == USB_ID(0x04fa, 0x4201))
		num = 4;

	for (i = 0; i < num; i++) {
		alts = &iface->altsetting[i];
		altsd = get_iface_desc(alts);
		protocol = altsd->bInterfaceProtocol;
		/* skip invalid one */
		if (((altsd->bInterfaceClass != USB_CLASS_AUDIO ||
		      (altsd->bInterfaceSubClass != USB_SUBCLASS_AUDIOSTREAMING &&
		       altsd->bInterfaceSubClass != USB_SUBCLASS_VENDOR_SPEC)) &&
		     altsd->bInterfaceClass != USB_CLASS_VENDOR_SPEC) ||
		    altsd->bNumEndpoints < 1 ||
		    le16_to_cpu(get_endpoint(alts, 0)->wMaxPacketSize) == 0)
			continue;
		/* must be isochronous */
		if ((get_endpoint(alts, 0)->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) !=
		    USB_ENDPOINT_XFER_ISOC)
			continue;
		/* check direction */
		stream = (get_endpoint(alts, 0)->bEndpointAddress & USB_DIR_IN) ?
			SNDRV_PCM_STREAM_CAPTURE : SNDRV_PCM_STREAM_PLAYBACK;
		altno = altsd->bAlternateSetting;

		if (snd_usb_apply_interface_quirk(chip, iface_no, altno))
			continue;

		/*
		 * Roland audio streaming interfaces are marked with protocols
		 * 0/1/2, but are UAC 1 compatible.
		 */
		if (USB_ID_VENDOR(chip->usb_id) == 0x0582 &&
		    altsd->bInterfaceClass == USB_CLASS_VENDOR_SPEC &&
		    protocol <= 2)
			protocol = UAC_VERSION_1;

		switch (protocol) {
		default:
			dev_dbg(&dev->dev, "%u:%d: unknown interface protocol %#02x, assuming v1\n",
				iface_no, altno, protocol);
			protocol = UAC_VERSION_1;
			/* fall through */
		case UAC_VERSION_1:
			/* fall through */
		case UAC_VERSION_2: {
			int bm_quirk = 0;

			/*
			 * Blue Microphones workaround: The last altsetting is
			 * identical with the previous one, except for a larger
			 * packet size, but is actually a mislabeled two-channel
			 * setting; ignore it.
			 *
			 * Part 1: prepare quirk flag
			 */
			if (altno == 2 && num == 3 &&
			    fp && fp->altsetting == 1 && fp->channels == 1 &&
			    fp->formats == SNDRV_PCM_FMTBIT_S16_LE &&
			    protocol == UAC_VERSION_1 &&
			    le16_to_cpu(get_endpoint(alts, 0)->wMaxPacketSize) ==
							fp->maxpacksize * 2)
				bm_quirk = 1;

			fp = snd_usb_get_audioformat_uac12(chip, alts, protocol,
							   iface_no, i, altno,
							   stream, bm_quirk);
			break;
		}
		case UAC_VERSION_3:
			fp = snd_usb_get_audioformat_uac3(chip, alts, &pd,
						iface_no, i, altno, stream);
			break;
		}

		if (!fp)
			continue;
		else if (IS_ERR(fp))
			return PTR_ERR(fp);

		if (fp->fmt_type != UAC_FORMAT_TYPE_I)
			*has_non_pcm = true;
		if ((fp->fmt_type == UAC_FORMAT_TYPE_I) == non_pcm) {
			audioformat_free(fp);
			kfree(pd);
			fp = NULL;
			pd = NULL;
			continue;
		}

		dev_dbg(&dev->dev, "%u:%d: add audio endpoint %#x\n", iface_no, altno, fp->endpoint);
		if (protocol == UAC_VERSION_3)
			err = snd_usb_add_audio_stream_v3(chip, stream, fp, pd);
		else
			err = snd_usb_add_audio_stream(chip, stream, fp);

		if (err < 0) {
			audioformat_free(fp);
			kfree(pd);
			return err;
		}
		/* try to set the interface... */
		usb_set_interface(chip->dev, iface_no, altno);
		snd_usb_init_pitch(chip, iface_no, alts, fp);
		snd_usb_init_sample_rate(chip, iface_no, alts, fp, fp->rate_max);
	}
	return 0;
}