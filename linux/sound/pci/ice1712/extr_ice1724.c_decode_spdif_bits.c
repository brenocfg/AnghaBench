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
struct snd_aes_iec958 {unsigned int* status; } ;

/* Variables and functions */
 unsigned int IEC958_AES0_CON_EMPHASIS_5015 ; 
 unsigned int IEC958_AES0_PRO_EMPHASIS_5015 ; 
 unsigned int IEC958_AES0_PRO_FS_32000 ; 
 unsigned int IEC958_AES0_PRO_FS_48000 ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void decode_spdif_bits(struct snd_aes_iec958 *diga, unsigned int val)
{
	memset(diga->status, 0, sizeof(diga->status));
	diga->status[0] = val & 0x03; /* professional, non-audio */
	if (val & 0x01) {
		/* professional */
		if (val & (1U << 3))
			diga->status[0] |= IEC958_AES0_PRO_EMPHASIS_5015;
		switch ((val >> 12) & 0x7) {
		case 0:
			break;
		case 2:
			diga->status[0] |= IEC958_AES0_PRO_FS_32000;
			break;
		default:
			diga->status[0] |= IEC958_AES0_PRO_FS_48000;
			break;
		}
	} else {
		/* consumer */
		diga->status[0] |= val & (1U << 2); /* copyright */
		if (val & (1U << 3))
			diga->status[0] |= IEC958_AES0_CON_EMPHASIS_5015;
		diga->status[1] |= (val >> 4) & 0x3f; /* category */
		diga->status[3] |= (val >> 12) & 0x07; /* fs */
	}
}