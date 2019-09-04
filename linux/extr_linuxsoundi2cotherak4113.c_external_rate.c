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
 unsigned char AK4113_FS0 ; 
 unsigned char AK4113_FS1 ; 
 unsigned char AK4113_FS2 ; 
 unsigned char AK4113_FS3 ; 
#define  AK4113_FS_11025HZ 140 
#define  AK4113_FS_16000HZ 139 
#define  AK4113_FS_176400HZ 138 
#define  AK4113_FS_192000HZ 137 
#define  AK4113_FS_22050HZ 136 
#define  AK4113_FS_24000HZ 135 
#define  AK4113_FS_32000HZ 134 
#define  AK4113_FS_44100HZ 133 
#define  AK4113_FS_48000HZ 132 
#define  AK4113_FS_64000HZ 131 
#define  AK4113_FS_8000HZ 130 
#define  AK4113_FS_88200HZ 129 
#define  AK4113_FS_96000HZ 128 

__attribute__((used)) static unsigned int external_rate(unsigned char rcs1)
{
	switch (rcs1 & (AK4113_FS0|AK4113_FS1|AK4113_FS2|AK4113_FS3)) {
	case AK4113_FS_8000HZ:
		return 8000;
	case AK4113_FS_11025HZ:
		return 11025;
	case AK4113_FS_16000HZ:
		return 16000;
	case AK4113_FS_22050HZ:
		return 22050;
	case AK4113_FS_24000HZ:
		return 24000;
	case AK4113_FS_32000HZ:
		return 32000;
	case AK4113_FS_44100HZ:
		return 44100;
	case AK4113_FS_48000HZ:
		return 48000;
	case AK4113_FS_64000HZ:
		return 64000;
	case AK4113_FS_88200HZ:
		return 88200;
	case AK4113_FS_96000HZ:
		return 96000;
	case AK4113_FS_176400HZ:
		return 176400;
	case AK4113_FS_192000HZ:
		return 192000;
	default:
		return 0;
	}
}