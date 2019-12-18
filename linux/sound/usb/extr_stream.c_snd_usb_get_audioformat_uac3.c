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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct usb_host_interface {int /*<<< orphan*/  extralen; int /*<<< orphan*/  extra; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct uac3_output_terminal_descriptor {int bCSourceID; } ;
struct uac3_input_terminal_descriptor {int bCSourceID; } ;
struct uac3_hc_descriptor_header {unsigned int channels; unsigned int bNrChannels; int /*<<< orphan*/  pd_d2d0_rec; int /*<<< orphan*/  pd_d1d0_rec; int /*<<< orphan*/  pd_id; int /*<<< orphan*/  wLength; int /*<<< orphan*/ * map; } ;
struct uac3_cluster_header_descriptor {unsigned int channels; unsigned int bNrChannels; int /*<<< orphan*/  pd_d2d0_rec; int /*<<< orphan*/  pd_d1d0_rec; int /*<<< orphan*/  pd_id; int /*<<< orphan*/  wLength; int /*<<< orphan*/ * map; } ;
struct uac3_as_header_descriptor {int bLength; int /*<<< orphan*/  bTerminalLink; int /*<<< orphan*/  wClusterDescrID; } ;
struct snd_usb_power_domain {unsigned int channels; unsigned int bNrChannels; int /*<<< orphan*/  pd_d2d0_rec; int /*<<< orphan*/  pd_d1d0_rec; int /*<<< orphan*/  pd_id; int /*<<< orphan*/  wLength; int /*<<< orphan*/ * map; } ;
struct snd_usb_audio {unsigned char badd_profile; int /*<<< orphan*/  ctrl_intf; struct usb_device* dev; } ;
struct snd_pcm_chmap_elem {unsigned int channels; unsigned int bNrChannels; int /*<<< orphan*/  pd_d2d0_rec; int /*<<< orphan*/  pd_d1d0_rec; int /*<<< orphan*/  pd_id; int /*<<< orphan*/  wLength; int /*<<< orphan*/ * map; } ;
struct audioformat {scalar_t__ attributes; int /*<<< orphan*/  rates; void* rate_max; void* rate_min; scalar_t__ nr_rates; int /*<<< orphan*/  formats; int /*<<< orphan*/  fmt_type; struct uac3_hc_descriptor_header* chmap; } ;
typedef  int /*<<< orphan*/  hc_header ;
struct TYPE_2__ {int /*<<< orphan*/  wMaxPacketSize; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 struct audioformat* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_CHMAP_FL ; 
 int /*<<< orphan*/  SNDRV_CHMAP_FR ; 
 int /*<<< orphan*/  SNDRV_CHMAP_MONO ; 
 int /*<<< orphan*/  SNDRV_PCM_FMTBIT_S16_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_FMTBIT_S24_3LE ; 
 int /*<<< orphan*/  SNDRV_PCM_RATE_CONTINUOUS ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int UAC3_BADD_CS_ID9 ; 
#define  UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_16 135 
#define  UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_24 134 
#define  UAC3_BADD_EP_MAXPSIZE_ASYNC_STEREO_16 133 
#define  UAC3_BADD_EP_MAXPSIZE_ASYNC_STEREO_24 132 
#define  UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_16 131 
#define  UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_24 130 
#define  UAC3_BADD_EP_MAXPSIZE_SYNC_STEREO_16 129 
#define  UAC3_BADD_EP_MAXPSIZE_SYNC_STEREO_24 128 
 int /*<<< orphan*/  UAC3_BADD_PD_ID10 ; 
 int /*<<< orphan*/  UAC3_BADD_PD_ID11 ; 
 int /*<<< orphan*/  UAC3_BADD_PD_RECOVER_D1D0 ; 
 int /*<<< orphan*/  UAC3_BADD_PD_RECOVER_D2D0 ; 
 void* UAC3_BADD_SAMPLING_RATE ; 
 int /*<<< orphan*/  UAC3_CS_REQ_HIGH_CAPABILITY_DESCRIPTOR ; 
 unsigned char UAC3_FUNCTION_SUBCLASS_GENERIC_IO ; 
 int /*<<< orphan*/  UAC_AS_GENERAL ; 
 int /*<<< orphan*/  UAC_FORMAT_TYPE_I ; 
 int /*<<< orphan*/  UAC_VERSION_3 ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 struct audioformat* audio_format_alloc_init (struct snd_usb_audio*,struct usb_host_interface*,int /*<<< orphan*/ ,int,int,int,unsigned int,int) ; 
 int /*<<< orphan*/  audioformat_free (struct audioformat*) ; 
 struct uac3_hc_descriptor_header* convert_chmap_v3 (struct uac3_hc_descriptor_header*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int,...) ; 
 TYPE_1__* get_endpoint (struct usb_host_interface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct uac3_hc_descriptor_header*) ; 
 struct uac3_hc_descriptor_header* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ parse_uac_endpoint_attributes (struct snd_usb_audio*,struct usb_host_interface*,int /*<<< orphan*/ ,int) ; 
 int snd_usb_ctl_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct uac3_hc_descriptor_header*,int) ; 
 int /*<<< orphan*/  snd_usb_ctrl_intf (struct snd_usb_audio*) ; 
 struct uac3_as_header_descriptor* snd_usb_find_csint_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct uac3_input_terminal_descriptor* snd_usb_find_input_terminal_descriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uac3_output_terminal_descriptor* snd_usb_find_output_terminal_descriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uac3_hc_descriptor_header* snd_usb_find_power_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_usb_parse_audio_format_v3 (struct snd_usb_audio*,struct audioformat*,struct uac3_as_header_descriptor*,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct audioformat *
snd_usb_get_audioformat_uac3(struct snd_usb_audio *chip,
			     struct usb_host_interface *alts,
			     struct snd_usb_power_domain **pd_out,
			     int iface_no, int altset_idx,
			     int altno, int stream)
{
	struct usb_device *dev = chip->dev;
	struct uac3_input_terminal_descriptor *input_term;
	struct uac3_output_terminal_descriptor *output_term;
	struct uac3_cluster_header_descriptor *cluster;
	struct uac3_as_header_descriptor *as = NULL;
	struct uac3_hc_descriptor_header hc_header;
	struct snd_pcm_chmap_elem *chmap;
	struct snd_usb_power_domain *pd;
	unsigned char badd_profile;
	u64 badd_formats = 0;
	unsigned int num_channels;
	struct audioformat *fp;
	u16 cluster_id, wLength;
	int clock = 0;
	int err;

	badd_profile = chip->badd_profile;

	if (badd_profile >= UAC3_FUNCTION_SUBCLASS_GENERIC_IO) {
		unsigned int maxpacksize =
			le16_to_cpu(get_endpoint(alts, 0)->wMaxPacketSize);

		switch (maxpacksize) {
		default:
			dev_err(&dev->dev,
				"%u:%d : incorrect wMaxPacketSize for BADD profile\n",
				iface_no, altno);
			return NULL;
		case UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_16:
		case UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_16:
			badd_formats = SNDRV_PCM_FMTBIT_S16_LE;
			num_channels = 1;
			break;
		case UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_24:
		case UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_24:
			badd_formats = SNDRV_PCM_FMTBIT_S24_3LE;
			num_channels = 1;
			break;
		case UAC3_BADD_EP_MAXPSIZE_SYNC_STEREO_16:
		case UAC3_BADD_EP_MAXPSIZE_ASYNC_STEREO_16:
			badd_formats = SNDRV_PCM_FMTBIT_S16_LE;
			num_channels = 2;
			break;
		case UAC3_BADD_EP_MAXPSIZE_SYNC_STEREO_24:
		case UAC3_BADD_EP_MAXPSIZE_ASYNC_STEREO_24:
			badd_formats = SNDRV_PCM_FMTBIT_S24_3LE;
			num_channels = 2;
			break;
		}

		chmap = kzalloc(sizeof(*chmap), GFP_KERNEL);
		if (!chmap)
			return ERR_PTR(-ENOMEM);

		if (num_channels == 1) {
			chmap->map[0] = SNDRV_CHMAP_MONO;
		} else {
			chmap->map[0] = SNDRV_CHMAP_FL;
			chmap->map[1] = SNDRV_CHMAP_FR;
		}

		chmap->channels = num_channels;
		clock = UAC3_BADD_CS_ID9;
		goto found_clock;
	}

	as = snd_usb_find_csint_desc(alts->extra, alts->extralen,
				     NULL, UAC_AS_GENERAL);
	if (!as) {
		dev_err(&dev->dev,
			"%u:%d : UAC_AS_GENERAL descriptor not found\n",
			iface_no, altno);
		return NULL;
	}

	if (as->bLength < sizeof(*as)) {
		dev_err(&dev->dev,
			"%u:%d : invalid UAC_AS_GENERAL desc\n",
			iface_no, altno);
		return NULL;
	}

	cluster_id = le16_to_cpu(as->wClusterDescrID);
	if (!cluster_id) {
		dev_err(&dev->dev,
			"%u:%d : no cluster descriptor\n",
			iface_no, altno);
		return NULL;
	}

	/*
	 * Get number of channels and channel map through
	 * High Capability Cluster Descriptor
	 *
	 * First step: get High Capability header and
	 * read size of Cluster Descriptor
	 */
	err = snd_usb_ctl_msg(chip->dev,
			usb_rcvctrlpipe(chip->dev, 0),
			UAC3_CS_REQ_HIGH_CAPABILITY_DESCRIPTOR,
			USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_DIR_IN,
			cluster_id,
			snd_usb_ctrl_intf(chip),
			&hc_header, sizeof(hc_header));
	if (err < 0)
		return ERR_PTR(err);
	else if (err != sizeof(hc_header)) {
		dev_err(&dev->dev,
			"%u:%d : can't get High Capability descriptor\n",
			iface_no, altno);
		return ERR_PTR(-EIO);
	}

	/*
	 * Second step: allocate needed amount of memory
	 * and request Cluster Descriptor
	 */
	wLength = le16_to_cpu(hc_header.wLength);
	cluster = kzalloc(wLength, GFP_KERNEL);
	if (!cluster)
		return ERR_PTR(-ENOMEM);
	err = snd_usb_ctl_msg(chip->dev,
			usb_rcvctrlpipe(chip->dev, 0),
			UAC3_CS_REQ_HIGH_CAPABILITY_DESCRIPTOR,
			USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_DIR_IN,
			cluster_id,
			snd_usb_ctrl_intf(chip),
			cluster, wLength);
	if (err < 0) {
		kfree(cluster);
		return ERR_PTR(err);
	} else if (err != wLength) {
		dev_err(&dev->dev,
			"%u:%d : can't get Cluster Descriptor\n",
			iface_no, altno);
		kfree(cluster);
		return ERR_PTR(-EIO);
	}

	num_channels = cluster->bNrChannels;
	chmap = convert_chmap_v3(cluster);
	kfree(cluster);

	/*
	 * lookup the terminal associated to this interface
	 * to extract the clock
	 */
	input_term = snd_usb_find_input_terminal_descriptor(chip->ctrl_intf,
							    as->bTerminalLink,
							    UAC_VERSION_3);
	if (input_term) {
		clock = input_term->bCSourceID;
		goto found_clock;
	}

	output_term = snd_usb_find_output_terminal_descriptor(chip->ctrl_intf,
							      as->bTerminalLink,
							      UAC_VERSION_3);
	if (output_term) {
		clock = output_term->bCSourceID;
		goto found_clock;
	}

	dev_err(&dev->dev, "%u:%d : bogus bTerminalLink %d\n",
			iface_no, altno, as->bTerminalLink);
	kfree(chmap);
	return NULL;

found_clock:
	fp = audio_format_alloc_init(chip, alts, UAC_VERSION_3, iface_no,
				     altset_idx, altno, num_channels, clock);
	if (!fp) {
		kfree(chmap);
		return ERR_PTR(-ENOMEM);
	}

	fp->chmap = chmap;

	if (badd_profile >= UAC3_FUNCTION_SUBCLASS_GENERIC_IO) {
		fp->attributes = 0; /* No attributes */

		fp->fmt_type = UAC_FORMAT_TYPE_I;
		fp->formats = badd_formats;

		fp->nr_rates = 0;	/* SNDRV_PCM_RATE_CONTINUOUS */
		fp->rate_min = UAC3_BADD_SAMPLING_RATE;
		fp->rate_max = UAC3_BADD_SAMPLING_RATE;
		fp->rates = SNDRV_PCM_RATE_CONTINUOUS;

		pd = kzalloc(sizeof(*pd), GFP_KERNEL);
		if (!pd) {
			audioformat_free(fp);
			return NULL;
		}
		pd->pd_id = (stream == SNDRV_PCM_STREAM_PLAYBACK) ?
					UAC3_BADD_PD_ID10 : UAC3_BADD_PD_ID11;
		pd->pd_d1d0_rec = UAC3_BADD_PD_RECOVER_D1D0;
		pd->pd_d2d0_rec = UAC3_BADD_PD_RECOVER_D2D0;

	} else {
		fp->attributes = parse_uac_endpoint_attributes(chip, alts,
							       UAC_VERSION_3,
							       iface_no);

		pd = snd_usb_find_power_domain(chip->ctrl_intf,
					       as->bTerminalLink);

		/* ok, let's parse further... */
		if (snd_usb_parse_audio_format_v3(chip, fp, as, stream) < 0) {
			kfree(pd);
			audioformat_free(fp);
			return NULL;
		}
	}

	if (pd)
		*pd_out = pd;

	return fp;
}