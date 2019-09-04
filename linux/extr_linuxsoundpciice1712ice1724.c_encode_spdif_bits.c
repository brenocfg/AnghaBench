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
struct snd_aes_iec958 {int* status; } ;

/* Variables and functions */
 int IEC958_AES0_CON_EMPHASIS ; 
 int IEC958_AES0_CON_EMPHASIS_5015 ; 
 int IEC958_AES0_PRO_EMPHASIS ; 
 int IEC958_AES0_PRO_EMPHASIS_5015 ; 
 int IEC958_AES0_PRO_FS ; 
#define  IEC958_AES0_PRO_FS_32000 129 
#define  IEC958_AES0_PRO_FS_44100 128 
 int IEC958_AES3_CON_FS ; 

__attribute__((used)) static unsigned int encode_spdif_bits(struct snd_aes_iec958 *diga)
{
	unsigned int val, rbits;

	val = diga->status[0] & 0x03; /* professional, non-audio */
	if (val & 0x01) {
		/* professional */
		if ((diga->status[0] & IEC958_AES0_PRO_EMPHASIS) ==
		    IEC958_AES0_PRO_EMPHASIS_5015)
			val |= 1U << 3;
		rbits = (diga->status[4] >> 3) & 0x0f;
		if (rbits) {
			switch (rbits) {
			case 2: val |= 5 << 12; break; /* 96k */
			case 3: val |= 6 << 12; break; /* 192k */
			case 10: val |= 4 << 12; break; /* 88.2k */
			case 11: val |= 7 << 12; break; /* 176.4k */
			}
		} else {
			switch (diga->status[0] & IEC958_AES0_PRO_FS) {
			case IEC958_AES0_PRO_FS_44100:
				break;
			case IEC958_AES0_PRO_FS_32000:
				val |= 3U << 12;
				break;
			default:
				val |= 2U << 12;
				break;
			}
		}
	} else {
		/* consumer */
		val |= diga->status[1] & 0x04; /* copyright */
		if ((diga->status[0] & IEC958_AES0_CON_EMPHASIS) ==
		    IEC958_AES0_CON_EMPHASIS_5015)
			val |= 1U << 3;
		val |= (unsigned int)(diga->status[1] & 0x3f) << 4; /* category */
		val |= (unsigned int)(diga->status[3] & IEC958_AES3_CON_FS) << 12; /* fs */
	}
	return val;
}