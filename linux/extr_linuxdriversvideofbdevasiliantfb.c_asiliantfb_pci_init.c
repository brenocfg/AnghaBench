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
typedef  int /*<<< orphan*/  u32 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; TYPE_1__* resource; } ;
struct fb_info {int /*<<< orphan*/ * screen_base; int /*<<< orphan*/ * par; int /*<<< orphan*/ * pseudo_palette; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int IORESOURCE_MEM ; 
 struct fb_info* framebuffer_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int init_asiliant (struct fb_info*,unsigned long) ; 
 int /*<<< orphan*/ * ioremap (unsigned long,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 unsigned long pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 unsigned long pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct fb_info*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  release_mem_region (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  request_mem_region (unsigned long,unsigned long,char*) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asiliantfb_pci_init(struct pci_dev *dp,
			       const struct pci_device_id *ent)
{
	unsigned long addr, size;
	struct fb_info *p;
	int err;

	if ((dp->resource[0].flags & IORESOURCE_MEM) == 0)
		return -ENODEV;
	addr = pci_resource_start(dp, 0);
	size = pci_resource_len(dp, 0);
	if (addr == 0)
		return -ENODEV;
	if (!request_mem_region(addr, size, "asiliantfb"))
		return -EBUSY;

	p = framebuffer_alloc(sizeof(u32) * 16, &dp->dev);
	if (!p)	{
		release_mem_region(addr, size);
		return -ENOMEM;
	}
	p->pseudo_palette = p->par;
	p->par = NULL;

	p->screen_base = ioremap(addr, 0x800000);
	if (p->screen_base == NULL) {
		release_mem_region(addr, size);
		framebuffer_release(p);
		return -ENOMEM;
	}

	pci_write_config_dword(dp, 4, 0x02800083);
	writeb(3, p->screen_base + 0x400784);

	err = init_asiliant(p, addr);
	if (err) {
		iounmap(p->screen_base);
		release_mem_region(addr, size);
		framebuffer_release(p);
		return err;
	}

	pci_set_drvdata(dp, p);
	return 0;
}