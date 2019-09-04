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
struct fb_image {int dummy; } ;

/* Variables and functions */

void xxxfb_imageblit(struct fb_info *p, const struct fb_image *image) 
{
/*
 *      @dx: The x and y coordinates of the upper left hand corner of the
 *	@dy: destination area to place the image on the screen.
 *      @width: How wide the image is we want to copy.
 *      @height: How tall the image is we want to copy.
 *      @fg_color: For mono bitmap images this is color data for     
 *      @bg_color: the foreground and background of the image to
 *		   write directly to the frmaebuffer.
 *	@depth:	How many bits represent a single pixel for this image.
 *	@data: The actual data used to construct the image on the display.
 *	@cmap: The colormap used for color images.   
 */

/*
 * The generic function, cfb_imageblit, expects that the bitmap scanlines are
 * padded to the next byte.  Most hardware accelerators may require padding to
 * the next u16 or the next u32.  If that is the case, the driver can specify
 * this by setting info->pixmap.scan_align = 2 or 4.  See a more
 * comprehensive description of the pixmap below.
 */
}