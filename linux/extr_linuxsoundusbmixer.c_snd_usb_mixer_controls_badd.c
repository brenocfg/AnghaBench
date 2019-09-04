#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usbmix_ctl_map {int id; int /*<<< orphan*/  map; } ;
struct usb_mixer_interface {TYPE_1__* chip; } ;
struct usb_interface_descriptor {int bNumEndpoints; } ;
struct usb_interface_assoc_descriptor {int bInterfaceCount; int bFirstInterface; } ;
struct usb_interface {int num_altsetting; struct usb_host_interface* altsetting; struct usb_interface_assoc_descriptor* intf_assoc; } ;
struct usb_host_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct usb_audio_term {void* type; int /*<<< orphan*/  id; } ;
struct uac3_badd_profile {int subclass; int st_chmask; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  oterm ;
typedef  int /*<<< orphan*/  iterm ;
struct TYPE_5__ {char bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_4__ {int badd_profile; struct usb_device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_16 135 
#define  UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_24 134 
#define  UAC3_BADD_EP_MAXPSIZE_ASYNC_STEREO_16 133 
#define  UAC3_BADD_EP_MAXPSIZE_ASYNC_STEREO_24 132 
#define  UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_16 131 
#define  UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_24 130 
#define  UAC3_BADD_EP_MAXPSIZE_SYNC_STEREO_16 129 
#define  UAC3_BADD_EP_MAXPSIZE_SYNC_STEREO_24 128 
 int /*<<< orphan*/  UAC3_BADD_FU_ID2 ; 
 int /*<<< orphan*/  UAC3_BADD_FU_ID5 ; 
 int /*<<< orphan*/  UAC3_BADD_FU_ID7 ; 
 int /*<<< orphan*/  UAC3_BADD_IT_ID4 ; 
 int /*<<< orphan*/  UAC3_BADD_OT_ID3 ; 
 int UAC3_FUNCTION_SUBCLASS_HEADSET_ADAPTER ; 
 void* UAC_BIDIR_TERMINAL_HEADSET ; 
 int /*<<< orphan*/  UAC_FU_MUTE ; 
 int /*<<< orphan*/  UAC_FU_VOLUME ; 
 char USB_DIR_IN ; 
 int /*<<< orphan*/  build_connector_control (struct usb_mixer_interface*,struct usb_audio_term*,int) ; 
 int /*<<< orphan*/  build_feature_ctl_badd (struct usb_mixer_interface*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* get_endpoint (struct usb_host_interface*,int /*<<< orphan*/ ) ; 
 struct usb_interface_descriptor* get_iface_desc (struct usb_host_interface*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct usb_audio_term*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uac3_badd_func_has_valid_channels (struct usb_mixer_interface*,struct uac3_badd_profile*,int,int) ; 
 struct uac3_badd_profile* uac3_badd_profiles ; 
 struct usbmix_ctl_map* uac3_badd_usbmix_ctl_maps ; 
 int /*<<< orphan*/  usb_audio_dbg (TYPE_1__*,char*,int,int,int) ; 
 int /*<<< orphan*/  usb_audio_err (TYPE_1__*,char*,unsigned int) ; 
 struct usb_interface* usb_ifnum_to_if (struct usb_device*,int) ; 

__attribute__((used)) static int snd_usb_mixer_controls_badd(struct usb_mixer_interface *mixer,
				       int ctrlif)
{
	struct usb_device *dev = mixer->chip->dev;
	struct usb_interface_assoc_descriptor *assoc;
	int badd_profile = mixer->chip->badd_profile;
	struct uac3_badd_profile *f;
	const struct usbmix_ctl_map *map;
	int p_chmask = 0, c_chmask = 0, st_chmask = 0;
	int i;

	assoc = usb_ifnum_to_if(dev, ctrlif)->intf_assoc;

	/* Detect BADD capture/playback channels from AS EP descriptors */
	for (i = 0; i < assoc->bInterfaceCount; i++) {
		int intf = assoc->bFirstInterface + i;

		struct usb_interface *iface;
		struct usb_host_interface *alts;
		struct usb_interface_descriptor *altsd;
		unsigned int maxpacksize;
		char dir_in;
		int chmask, num;

		if (intf == ctrlif)
			continue;

		iface = usb_ifnum_to_if(dev, intf);
		num = iface->num_altsetting;

		if (num < 2)
			return -EINVAL;

		/*
		 * The number of Channels in an AudioStreaming interface
		 * and the audio sample bit resolution (16 bits or 24
		 * bits) can be derived from the wMaxPacketSize field in
		 * the Standard AS Audio Data Endpoint descriptor in
		 * Alternate Setting 1
		 */
		alts = &iface->altsetting[1];
		altsd = get_iface_desc(alts);

		if (altsd->bNumEndpoints < 1)
			return -EINVAL;

		/* check direction */
		dir_in = (get_endpoint(alts, 0)->bEndpointAddress & USB_DIR_IN);
		maxpacksize = le16_to_cpu(get_endpoint(alts, 0)->wMaxPacketSize);

		switch (maxpacksize) {
		default:
			usb_audio_err(mixer->chip,
				"incorrect wMaxPacketSize 0x%x for BADD profile\n",
				maxpacksize);
			return -EINVAL;
		case UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_16:
		case UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_16:
		case UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_24:
		case UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_24:
			chmask = 1;
			break;
		case UAC3_BADD_EP_MAXPSIZE_SYNC_STEREO_16:
		case UAC3_BADD_EP_MAXPSIZE_ASYNC_STEREO_16:
		case UAC3_BADD_EP_MAXPSIZE_SYNC_STEREO_24:
		case UAC3_BADD_EP_MAXPSIZE_ASYNC_STEREO_24:
			chmask = 3;
			break;
		}

		if (dir_in)
			c_chmask = chmask;
		else
			p_chmask = chmask;
	}

	usb_audio_dbg(mixer->chip,
		"UAC3 BADD profile 0x%x: detected c_chmask=%d p_chmask=%d\n",
		badd_profile, c_chmask, p_chmask);

	/* check the mapping table */
	for (map = uac3_badd_usbmix_ctl_maps; map->id; map++) {
		if (map->id == badd_profile)
			break;
	}

	if (!map->id)
		return -EINVAL;

	for (f = uac3_badd_profiles; f->name; f++) {
		if (badd_profile == f->subclass)
			break;
	}
	if (!f->name)
		return -EINVAL;
	if (!uac3_badd_func_has_valid_channels(mixer, f, c_chmask, p_chmask))
		return -EINVAL;
	st_chmask = f->st_chmask;

	/* Playback */
	if (p_chmask) {
		/* Master channel, always writable */
		build_feature_ctl_badd(mixer, 0, UAC_FU_MUTE,
				       UAC3_BADD_FU_ID2, map->map);
		/* Mono/Stereo volume channels, always writable */
		build_feature_ctl_badd(mixer, p_chmask, UAC_FU_VOLUME,
				       UAC3_BADD_FU_ID2, map->map);
	}

	/* Capture */
	if (c_chmask) {
		/* Master channel, always writable */
		build_feature_ctl_badd(mixer, 0, UAC_FU_MUTE,
				       UAC3_BADD_FU_ID5, map->map);
		/* Mono/Stereo volume channels, always writable */
		build_feature_ctl_badd(mixer, c_chmask, UAC_FU_VOLUME,
				       UAC3_BADD_FU_ID5, map->map);
	}

	/* Side tone-mixing */
	if (st_chmask) {
		/* Master channel, always writable */
		build_feature_ctl_badd(mixer, 0, UAC_FU_MUTE,
				       UAC3_BADD_FU_ID7, map->map);
		/* Mono volume channel, always writable */
		build_feature_ctl_badd(mixer, 1, UAC_FU_VOLUME,
				       UAC3_BADD_FU_ID7, map->map);
	}

	/* Insertion Control */
	if (f->subclass == UAC3_FUNCTION_SUBCLASS_HEADSET_ADAPTER) {
		struct usb_audio_term iterm, oterm;

		/* Input Term - Insertion control */
		memset(&iterm, 0, sizeof(iterm));
		iterm.id = UAC3_BADD_IT_ID4;
		iterm.type = UAC_BIDIR_TERMINAL_HEADSET;
		build_connector_control(mixer, &iterm, true);

		/* Output Term - Insertion control */
		memset(&oterm, 0, sizeof(oterm));
		oterm.id = UAC3_BADD_OT_ID3;
		oterm.type = UAC_BIDIR_TERMINAL_HEADSET;
		build_connector_control(mixer, &oterm, false);
	}

	return 0;
}