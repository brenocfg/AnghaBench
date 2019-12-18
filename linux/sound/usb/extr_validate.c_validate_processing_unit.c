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
struct usb_desc_validator {int protocol; int /*<<< orphan*/  type; } ;
struct uac_processing_unit_descriptor {int bLength; int bNrInPins; int /*<<< orphan*/  wProcessType; } ;

/* Variables and functions */
 int /*<<< orphan*/  UAC1_EXTENSION_UNIT ; 
 int /*<<< orphan*/  UAC2_EXTENSION_UNIT_V2 ; 
 int /*<<< orphan*/  UAC2_PROCESSING_UNIT_V2 ; 
#define  UAC2_PROCESS_DOLBY_PROLOCIC 136 
#define  UAC2_PROCESS_UP_DOWNMIX 135 
 int /*<<< orphan*/  UAC3_EXTENSION_UNIT ; 
#define  UAC3_PROCESS_MULTI_FUNCTION 134 
#define  UAC3_PROCESS_UP_DOWNMIX 133 
#define  UAC_PROCESS_DOLBY_PROLOGIC 132 
#define  UAC_PROCESS_UP_DOWNMIX 131 
#define  UAC_VERSION_1 130 
#define  UAC_VERSION_2 129 
#define  UAC_VERSION_3 128 

__attribute__((used)) static bool validate_processing_unit(const void *p,
				     const struct usb_desc_validator *v)
{
	const struct uac_processing_unit_descriptor *d = p;
	const unsigned char *hdr = p;
	size_t len, m;

	if (d->bLength < sizeof(*d))
		return false;
	len = sizeof(*d) + d->bNrInPins;
	if (d->bLength < len)
		return false;
	switch (v->protocol) {
	case UAC_VERSION_1:
	default:
		/* bNrChannels, wChannelConfig, iChannelNames, bControlSize */
		len += 1 + 2 + 1 + 1;
		if (d->bLength < len) /* bControlSize */
			return false;
		m = hdr[len];
		len += 1 + m + 1; /* bControlSize, bmControls, iProcessing */
		break;
	case UAC_VERSION_2:
		/* bNrChannels, bmChannelConfig, iChannelNames */
		len += 1 + 4 + 1;
		if (v->type == UAC2_PROCESSING_UNIT_V2)
			len += 2; /* bmControls -- 2 bytes for PU */
		else
			len += 1; /* bmControls -- 1 byte for EU */
		len += 1; /* iProcessing */
		break;
	case UAC_VERSION_3:
		/* wProcessingDescrStr, bmControls */
		len += 2 + 4;
		break;
	}
	if (d->bLength < len)
		return false;

	switch (v->protocol) {
	case UAC_VERSION_1:
	default:
		if (v->type == UAC1_EXTENSION_UNIT)
			return true; /* OK */
		switch (d->wProcessType) {
		case UAC_PROCESS_UP_DOWNMIX:
		case UAC_PROCESS_DOLBY_PROLOGIC:
			if (d->bLength < len + 1) /* bNrModes */
				return false;
			m = hdr[len];
			len += 1 + m * 2; /* bNrModes, waModes(n) */
			break;
		default:
			break;
		}
		break;
	case UAC_VERSION_2:
		if (v->type == UAC2_EXTENSION_UNIT_V2)
			return true; /* OK */
		switch (d->wProcessType) {
		case UAC2_PROCESS_UP_DOWNMIX:
		case UAC2_PROCESS_DOLBY_PROLOCIC: /* SiC! */
			if (d->bLength < len + 1) /* bNrModes */
				return false;
			m = hdr[len];
			len += 1 + m * 4; /* bNrModes, daModes(n) */
			break;
		default:
			break;
		}
		break;
	case UAC_VERSION_3:
		if (v->type == UAC3_EXTENSION_UNIT) {
			len += 2; /* wClusterDescrID */
			break;
		}
		switch (d->wProcessType) {
		case UAC3_PROCESS_UP_DOWNMIX:
			if (d->bLength < len + 1) /* bNrModes */
				return false;
			m = hdr[len];
			len += 1 + m * 2; /* bNrModes, waClusterDescrID(n) */
			break;
		case UAC3_PROCESS_MULTI_FUNCTION:
			len += 2 + 4; /* wClusterDescrID, bmAlgorighms */
			break;
		default:
			break;
		}
		break;
	}
	if (d->bLength < len)
		return false;

	return true;
}