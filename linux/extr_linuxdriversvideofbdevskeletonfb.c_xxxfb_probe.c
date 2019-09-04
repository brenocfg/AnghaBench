#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xxx_par {int dummy; } ;
struct pci_device_id {int dummy; } ;
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int scan_align; int buf_align; int access_align; int /*<<< orphan*/  flags; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;
struct fb_info {TYPE_2__ fix; int /*<<< orphan*/  cmap; int /*<<< orphan*/  var; TYPE_1__ pixmap; int /*<<< orphan*/  flags; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/ * fbops; int /*<<< orphan*/  screen_base; struct xxx_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FBINFO_DEFAULT ; 
 int /*<<< orphan*/  FB_PIXMAP_SYSTEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PIXMAP_SIZE ; 
 scalar_t__ fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int fb_find_mode (int /*<<< orphan*/ *,struct fb_info*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fb_info (struct fb_info*,char*,int /*<<< orphan*/ ) ; 
 struct fb_info* framebuffer_alloc (int,struct device*) ; 
 int /*<<< orphan*/  framebuffer_virtual_memory ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* mode_option ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct fb_info*) ; 
 int /*<<< orphan*/  pseudo_palette ; 
 scalar_t__ register_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  xxxfb_check_var (int /*<<< orphan*/ *,struct fb_info*) ; 
 TYPE_2__ xxxfb_fix ; 
 int /*<<< orphan*/  xxxfb_ops ; 
 int /*<<< orphan*/  xxxfb_var ; 

__attribute__((used)) static int xxxfb_probe(struct pci_dev *dev, const struct pci_device_id *ent)
{
    struct fb_info *info;
    struct xxx_par *par;
    struct device *device = &dev->dev; /* or &pdev->dev */
    int cmap_len, retval;	
   
    /*
     * Dynamically allocate info and par
     */
    info = framebuffer_alloc(sizeof(struct xxx_par), device);

    if (!info) {
	    /* goto error path */
    }

    par = info->par;

    /* 
     * Here we set the screen_base to the virtual memory address
     * for the framebuffer. Usually we obtain the resource address
     * from the bus layer and then translate it to virtual memory
     * space via ioremap. Consult ioport.h. 
     */
    info->screen_base = framebuffer_virtual_memory;
    info->fbops = &xxxfb_ops;
    info->fix = xxxfb_fix;
    info->pseudo_palette = pseudo_palette; /* The pseudopalette is an
					    * 16-member array
					    */
    /*
     * Set up flags to indicate what sort of acceleration your
     * driver can provide (pan/wrap/copyarea/etc.) and whether it
     * is a module -- see FBINFO_* in include/linux/fb.h
     *
     * If your hardware can support any of the hardware accelerated functions
     * fbcon performance will improve if info->flags is set properly.
     *
     * FBINFO_HWACCEL_COPYAREA - hardware moves
     * FBINFO_HWACCEL_FILLRECT - hardware fills
     * FBINFO_HWACCEL_IMAGEBLIT - hardware mono->color expansion
     * FBINFO_HWACCEL_YPAN - hardware can pan display in y-axis
     * FBINFO_HWACCEL_YWRAP - hardware can wrap display in y-axis
     * FBINFO_HWACCEL_DISABLED - supports hardware accels, but disabled
     * FBINFO_READS_FAST - if set, prefer moves over mono->color expansion
     * FBINFO_MISC_TILEBLITTING - hardware can do tile blits
     *
     * NOTE: These are for fbcon use only.
     */
    info->flags = FBINFO_DEFAULT;

/********************* This stage is optional ******************************/
     /*
     * The struct pixmap is a scratch pad for the drawing functions. This
     * is where the monochrome bitmap is constructed by the higher layers
     * and then passed to the accelerator.  For drivers that uses
     * cfb_imageblit, you can skip this part.  For those that have a more
     * rigorous requirement, this stage is needed
     */

    /* PIXMAP_SIZE should be small enough to optimize drawing, but not
     * large enough that memory is wasted.  A safe size is
     * (max_xres * max_font_height/8). max_xres is driver dependent,
     * max_font_height is 32.
     */
    info->pixmap.addr = kmalloc(PIXMAP_SIZE, GFP_KERNEL);
    if (!info->pixmap.addr) {
	    /* goto error */
    }

    info->pixmap.size = PIXMAP_SIZE;

    /*
     * FB_PIXMAP_SYSTEM - memory is in system ram
     * FB_PIXMAP_IO     - memory is iomapped
     * FB_PIXMAP_SYNC   - if set, will call fb_sync() per access to pixmap,
     *                    usually if FB_PIXMAP_IO is set.
     *
     * Currently, FB_PIXMAP_IO is unimplemented.
     */
    info->pixmap.flags = FB_PIXMAP_SYSTEM;

    /*
     * scan_align is the number of padding for each scanline.  It is in bytes.
     * Thus for accelerators that need padding to the next u32, put 4 here.
     */
    info->pixmap.scan_align = 4;

    /*
     * buf_align is the amount to be padded for the buffer. For example,
     * the i810fb needs a scan_align of 2 but expects it to be fed with
     * dwords, so a buf_align = 4 is required.
     */
    info->pixmap.buf_align = 4;

    /* access_align is how many bits can be accessed from the framebuffer
     * ie. some epson cards allow 16-bit access only.  Most drivers will
     * be safe with u32 here.
     *
     * NOTE: This field is currently unused.
     */
    info->pixmap.access_align = 32;
/***************************** End optional stage ***************************/

    /*
     * This should give a reasonable default video mode. The following is
     * done when we can set a video mode. 
     */
    if (!mode_option)
	mode_option = "640x480@60";	 	

    retval = fb_find_mode(&info->var, info, mode_option, NULL, 0, NULL, 8);
  
    if (!retval || retval == 4)
	return -EINVAL;			

    /* This has to be done! */
    if (fb_alloc_cmap(&info->cmap, cmap_len, 0))
	return -ENOMEM;
	
    /* 
     * The following is done in the case of having hardware with a static 
     * mode. If we are setting the mode ourselves we don't call this. 
     */	
    info->var = xxxfb_var;

    /*
     * For drivers that can...
     */
    xxxfb_check_var(&info->var, info);

    /*
     * Does a call to fb_set_par() before register_framebuffer needed?  This
     * will depend on you and the hardware.  If you are sure that your driver
     * is the only device in the system, a call to fb_set_par() is safe.
     *
     * Hardware in x86 systems has a VGA core.  Calling set_par() at this
     * point will corrupt the VGA console, so it might be safer to skip a
     * call to set_par here and just allow fbcon to do it for you.
     */
    /* xxxfb_set_par(info); */

    if (register_framebuffer(info) < 0) {
	fb_dealloc_cmap(&info->cmap);
	return -EINVAL;
    }
    fb_info(info, "%s frame buffer device\n", info->fix.id);
    pci_set_drvdata(dev, info); /* or platform_set_drvdata(pdev, info) */
    return 0;
}