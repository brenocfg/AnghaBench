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
struct xenfb_info {int dummy; } ;
struct fb_info {struct xenfb_info* par; } ;
struct fb_image {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;

/* Variables and functions */
 int /*<<< orphan*/  sys_imageblit (struct fb_info*,struct fb_image const*) ; 
 int /*<<< orphan*/  xenfb_refresh (struct xenfb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xenfb_imageblit(struct fb_info *p, const struct fb_image *image)
{
	struct xenfb_info *info = p->par;

	sys_imageblit(p, image);
	xenfb_refresh(info, image->dx, image->dy, image->width, image->height);
}