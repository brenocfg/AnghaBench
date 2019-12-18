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
 unsigned char AK4117_FS0 ; 
 unsigned char AK4117_FS1 ; 
 unsigned char AK4117_FS2 ; 
 unsigned char AK4117_FS3 ; 
#define  AK4117_FS_176400HZ 134 
#define  AK4117_FS_192000HZ 133 
#define  AK4117_FS_32000HZ 132 
#define  AK4117_FS_44100HZ 131 
#define  AK4117_FS_48000HZ 130 
#define  AK4117_FS_88200HZ 129 
#define  AK4117_FS_96000HZ 128 

__attribute__((used)) static unsigned int external_rate(unsigned char rcs1)
{
	switch (rcs1 & (AK4117_FS0|AK4117_FS1|AK4117_FS2|AK4117_FS3)) {
	case AK4117_FS_32000HZ: return 32000;
	case AK4117_FS_44100HZ: return 44100;
	case AK4117_FS_48000HZ: return 48000;
	case AK4117_FS_88200HZ: return 88200;
	case AK4117_FS_96000HZ: return 96000;
	case AK4117_FS_176400HZ: return 176400;
	case AK4117_FS_192000HZ: return 192000;
	default:		return 0;
	}
}