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

/* Variables and functions */
 unsigned int IEC958_AES3_CON_FS_176400 ; 
 unsigned int IEC958_AES3_CON_FS_192000 ; 
 unsigned int IEC958_AES3_CON_FS_32000 ; 
 unsigned int IEC958_AES3_CON_FS_44100 ; 
 unsigned int IEC958_AES3_CON_FS_48000 ; 
 unsigned int IEC958_AES3_CON_FS_88200 ; 
 unsigned int IEC958_AES3_CON_FS_96000 ; 
#define  OXYGEN_RATE_176400 134 
#define  OXYGEN_RATE_192000 133 
#define  OXYGEN_RATE_32000 132 
#define  OXYGEN_RATE_44100 131 
#define  OXYGEN_RATE_64000 130 
#define  OXYGEN_RATE_88200 129 
#define  OXYGEN_RATE_96000 128 
 unsigned int OXYGEN_SPDIF_CS_RATE_SHIFT ; 

__attribute__((used)) static unsigned int oxygen_spdif_rate(unsigned int oxygen_rate)
{
	switch (oxygen_rate) {
	case OXYGEN_RATE_32000:
		return IEC958_AES3_CON_FS_32000 << OXYGEN_SPDIF_CS_RATE_SHIFT;
	case OXYGEN_RATE_44100:
		return IEC958_AES3_CON_FS_44100 << OXYGEN_SPDIF_CS_RATE_SHIFT;
	default: /* OXYGEN_RATE_48000 */
		return IEC958_AES3_CON_FS_48000 << OXYGEN_SPDIF_CS_RATE_SHIFT;
	case OXYGEN_RATE_64000:
		return 0xb << OXYGEN_SPDIF_CS_RATE_SHIFT;
	case OXYGEN_RATE_88200:
		return IEC958_AES3_CON_FS_88200 << OXYGEN_SPDIF_CS_RATE_SHIFT;
	case OXYGEN_RATE_96000:
		return IEC958_AES3_CON_FS_96000 << OXYGEN_SPDIF_CS_RATE_SHIFT;
	case OXYGEN_RATE_176400:
		return IEC958_AES3_CON_FS_176400 << OXYGEN_SPDIF_CS_RATE_SHIFT;
	case OXYGEN_RATE_192000:
		return IEC958_AES3_CON_FS_192000 << OXYGEN_SPDIF_CS_RATE_SHIFT;
	}
}