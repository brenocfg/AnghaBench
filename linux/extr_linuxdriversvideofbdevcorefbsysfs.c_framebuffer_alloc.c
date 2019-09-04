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
struct fb_info {char* par; int fbcon_rotate_hint; struct device* device; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 

struct fb_info *framebuffer_alloc(size_t size, struct device *dev)
{
#define BYTES_PER_LONG (BITS_PER_LONG/8)
#define PADDING (BYTES_PER_LONG - (sizeof(struct fb_info) % BYTES_PER_LONG))
	int fb_info_size = sizeof(struct fb_info);
	struct fb_info *info;
	char *p;

	if (size)
		fb_info_size += PADDING;

	p = kzalloc(fb_info_size + size, GFP_KERNEL);

	if (!p)
		return NULL;

	info = (struct fb_info *) p;

	if (size)
		info->par = p + fb_info_size;

	info->device = dev;
	info->fbcon_rotate_hint = -1;

#ifdef CONFIG_FB_BACKLIGHT
	mutex_init(&info->bl_curve_mutex);
#endif

	return info;
#undef PADDING
#undef BYTES_PER_LONG
}