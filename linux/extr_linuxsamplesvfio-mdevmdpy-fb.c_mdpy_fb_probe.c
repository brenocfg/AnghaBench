#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mdpy_fb_par {int /*<<< orphan*/  palette; } ;
struct TYPE_7__ {int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; scalar_t__ line_length; } ;
struct TYPE_6__ {scalar_t__ yres_virtual; scalar_t__ xres_virtual; scalar_t__ yres; scalar_t__ xres; } ;
struct fb_info {int /*<<< orphan*/  screen_base; int /*<<< orphan*/  node; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/  flags; int /*<<< orphan*/ * fbops; TYPE_3__ fix; TYPE_4__* apertures; int /*<<< orphan*/  screen_size; TYPE_2__ var; struct mdpy_fb_par* par; } ;
struct TYPE_8__ {TYPE_1__* ranges; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ DRM_FORMAT_XRGB8888 ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FBINFO_DEFAULT ; 
 int /*<<< orphan*/  MDPY_FORMAT_OFFSET ; 
 int /*<<< orphan*/  MDPY_HEIGHT_OFFSET ; 
 int /*<<< orphan*/  MDPY_WIDTH_OFFSET ; 
 TYPE_4__* alloc_apertures (int) ; 
 struct fb_info* framebuffer_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 TYPE_3__ mdpy_fb_fix ; 
 int /*<<< orphan*/  mdpy_fb_ops ; 
 TYPE_2__ mdpy_fb_var ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,...) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct fb_info*) ; 
 int register_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int mdpy_fb_probe(struct pci_dev *pdev,
			 const struct pci_device_id *ent)
{
	struct fb_info *info;
	struct mdpy_fb_par *par;
	u32 format, width, height;
	int ret;

	ret = pci_enable_device(pdev);
	if (ret < 0)
		return ret;

	ret = pci_request_regions(pdev, "mdpy-fb");
	if (ret < 0)
		return ret;

	pci_read_config_dword(pdev, MDPY_FORMAT_OFFSET, &format);
	pci_read_config_dword(pdev, MDPY_WIDTH_OFFSET,	&width);
	pci_read_config_dword(pdev, MDPY_HEIGHT_OFFSET, &height);
	if (format != DRM_FORMAT_XRGB8888) {
		pci_err(pdev, "format mismatch (0x%x != 0x%x)\n",
			format, DRM_FORMAT_XRGB8888);
		return -EINVAL;
	}
	if (width < 100	 || width > 10000) {
		pci_err(pdev, "width (%d) out of range\n", width);
		return -EINVAL;
	}
	if (height < 100 || height > 10000) {
		pci_err(pdev, "height (%d) out of range\n", height);
		return -EINVAL;
	}
	pci_info(pdev, "mdpy found: %dx%d framebuffer\n",
		 width, height);

	info = framebuffer_alloc(sizeof(struct mdpy_fb_par), &pdev->dev);
	if (!info)
		goto err_release_regions;
	pci_set_drvdata(pdev, info);
	par = info->par;

	info->fix = mdpy_fb_fix;
	info->fix.smem_start = pci_resource_start(pdev, 0);
	info->fix.smem_len = pci_resource_len(pdev, 0);
	info->fix.line_length = width * 4;

	info->var = mdpy_fb_var;
	info->var.xres = width;
	info->var.yres = height;
	info->var.xres_virtual = width;
	info->var.yres_virtual = height;

	info->screen_size = info->fix.smem_len;
	info->screen_base = ioremap(info->fix.smem_start,
				    info->screen_size);
	if (!info->screen_base) {
		pci_err(pdev, "ioremap(pcibar) failed\n");
		ret = -EIO;
		goto err_release_fb;
	}

	info->apertures = alloc_apertures(1);
	if (!info->apertures) {
		ret = -ENOMEM;
		goto err_unmap;
	}
	info->apertures->ranges[0].base = info->fix.smem_start;
	info->apertures->ranges[0].size = info->fix.smem_len;

	info->fbops = &mdpy_fb_ops;
	info->flags = FBINFO_DEFAULT;
	info->pseudo_palette = par->palette;

	ret = register_framebuffer(info);
	if (ret < 0) {
		pci_err(pdev, "mdpy-fb device register failed: %d\n", ret);
		goto err_unmap;
	}

	pci_info(pdev, "fb%d registered\n", info->node);
	return 0;

err_unmap:
	iounmap(info->screen_base);

err_release_fb:
	framebuffer_release(info);

err_release_regions:
	pci_release_regions(pdev);

	return ret;
}