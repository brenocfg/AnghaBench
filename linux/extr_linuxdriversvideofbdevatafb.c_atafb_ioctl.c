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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
atafb_ioctl(struct fb_info *info, unsigned int cmd, unsigned long arg)
{
	switch (cmd) {
#ifdef FBCMD_GET_CURRENTPAR
	case FBCMD_GET_CURRENTPAR:
		if (copy_to_user((void *)arg, (void *)&current_par,
				 sizeof(struct atafb_par)))
			return -EFAULT;
		return 0;
#endif
#ifdef FBCMD_SET_CURRENTPAR
	case FBCMD_SET_CURRENTPAR:
		if (copy_from_user((void *)&current_par, (void *)arg,
				   sizeof(struct atafb_par)))
			return -EFAULT;
		ata_set_par(&current_par);
		return 0;
#endif
	}
	return -EINVAL;
}