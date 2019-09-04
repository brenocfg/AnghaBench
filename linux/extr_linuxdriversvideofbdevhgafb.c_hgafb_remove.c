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
struct platform_device {int dummy; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  hga_clear_screen () ; 
 int /*<<< orphan*/  hga_txt_mode () ; 
 int /*<<< orphan*/  hga_vram ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct fb_info* platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ release_io_port ; 
 scalar_t__ release_io_ports ; 
 int /*<<< orphan*/  release_region (int,int) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int hgafb_remove(struct platform_device *pdev)
{
	struct fb_info *info = platform_get_drvdata(pdev);

	hga_txt_mode();
	hga_clear_screen();

	if (info) {
		unregister_framebuffer(info);
		framebuffer_release(info);
	}

	iounmap(hga_vram);

	if (release_io_ports)
		release_region(0x3b0, 12);

	if (release_io_port)
		release_region(0x3bf, 1);

	return 0;
}