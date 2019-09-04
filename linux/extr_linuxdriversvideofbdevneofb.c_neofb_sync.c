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
struct TYPE_2__ {int accel; } ;
struct fb_info {TYPE_1__ fix; } ;

/* Variables and functions */
#define  FB_ACCEL_NEOMAGIC_NM2200 131 
#define  FB_ACCEL_NEOMAGIC_NM2230 130 
#define  FB_ACCEL_NEOMAGIC_NM2360 129 
#define  FB_ACCEL_NEOMAGIC_NM2380 128 
 int /*<<< orphan*/  neo2200_sync (struct fb_info*) ; 

__attribute__((used)) static int 
neofb_sync(struct fb_info *info)
{
	switch (info->fix.accel) {
		case FB_ACCEL_NEOMAGIC_NM2200:
		case FB_ACCEL_NEOMAGIC_NM2230: 
		case FB_ACCEL_NEOMAGIC_NM2360: 
		case FB_ACCEL_NEOMAGIC_NM2380: 
			neo2200_sync(info);
			break;
		default:
			break;
	}
	return 0;		
}