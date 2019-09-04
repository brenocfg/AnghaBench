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
struct TYPE_2__ {int /*<<< orphan*/  smem_len; } ;
struct fb_info {TYPE_1__ fix; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBTYPE_SUN3COLOR ; 
 int sbusfb_ioctl_helper (unsigned int,unsigned long,struct fb_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cg3_ioctl(struct fb_info *info, unsigned int cmd, unsigned long arg)
{
	return sbusfb_ioctl_helper(cmd, arg, info,
				   FBTYPE_SUN3COLOR, 8, info->fix.smem_len);
}