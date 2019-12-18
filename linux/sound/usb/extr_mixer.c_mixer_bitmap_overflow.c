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
typedef  int u8 ;
struct uac_mixer_unit_descriptor {int dummy; } ;

/* Variables and functions */
#define  UAC_VERSION_1 130 
#define  UAC_VERSION_2 129 
#define  UAC_VERSION_3 128 
 int* uac_mixer_unit_bmControls (struct uac_mixer_unit_descriptor*,int) ; 

__attribute__((used)) static bool mixer_bitmap_overflow(struct uac_mixer_unit_descriptor *desc,
				  int protocol, int num_ins, int num_outs)
{
	u8 *hdr = (u8 *)desc;
	u8 *c = uac_mixer_unit_bmControls(desc, protocol);
	size_t rest; /* remaining bytes after bmMixerControls */

	switch (protocol) {
	case UAC_VERSION_1:
	default:
		rest = 1; /* iMixer */
		break;
	case UAC_VERSION_2:
		rest = 2; /* bmControls + iMixer */
		break;
	case UAC_VERSION_3:
		rest = 6; /* bmControls + wMixerDescrStr */
		break;
	}

	/* overflow? */
	return c + (num_ins * num_outs + 7) / 8 + rest > hdr + hdr[0];
}