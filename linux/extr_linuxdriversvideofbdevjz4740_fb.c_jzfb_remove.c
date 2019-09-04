#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct jzfb {TYPE_1__* fb; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (TYPE_1__*) ; 
 int /*<<< orphan*/  jzfb_blank (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  jzfb_free_devmem (struct jzfb*) ; 
 struct jzfb* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int jzfb_remove(struct platform_device *pdev)
{
	struct jzfb *jzfb = platform_get_drvdata(pdev);

	jzfb_blank(FB_BLANK_POWERDOWN, jzfb->fb);

	fb_dealloc_cmap(&jzfb->fb->cmap);
	jzfb_free_devmem(jzfb);

	framebuffer_release(jzfb->fb);

	return 0;
}