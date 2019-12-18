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
struct TYPE_2__ {int vendor_id; } ;
struct hda_codec {TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad198x_power_eapd_write (struct hda_codec*,int,int) ; 

__attribute__((used)) static void ad198x_power_eapd(struct hda_codec *codec)
{
	/* We currently only handle front, HP */
	switch (codec->core.vendor_id) {
	case 0x11d41882:
	case 0x11d4882a:
	case 0x11d41884:
	case 0x11d41984:
	case 0x11d41883:
	case 0x11d4184a:
	case 0x11d4194a:
	case 0x11d4194b:
	case 0x11d41988:
	case 0x11d4198b:
	case 0x11d4989a:
	case 0x11d4989b:
		ad198x_power_eapd_write(codec, 0x12, 0x11);
		break;
	case 0x11d41981:
	case 0x11d41983:
		ad198x_power_eapd_write(codec, 0x05, 0x06);
		break;
	case 0x11d41986:
		ad198x_power_eapd_write(codec, 0x1b, 0x1a);
		break;
	}
}