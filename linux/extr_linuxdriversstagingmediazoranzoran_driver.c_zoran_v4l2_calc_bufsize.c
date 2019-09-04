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
struct zoran_jpg_settings {int VerDcm; int HorDcm; int TmpDcm; } ;
typedef  int __u8 ;
typedef  int __u32 ;

/* Variables and functions */
 int jpg_bufsize ; 

__attribute__((used)) static __u32
zoran_v4l2_calc_bufsize (struct zoran_jpg_settings *settings)
{
	__u8 div = settings->VerDcm * settings->HorDcm * settings->TmpDcm;
	__u32 num = (1024 * 512) / (div);
	__u32 result = 2;

	num--;
	while (num) {
		num >>= 1;
		result <<= 1;
	}

	if (result > jpg_bufsize)
		return jpg_bufsize;
	if (result < 8192)
		return 8192;
	return result;
}