#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int /*<<< orphan*/  cmap; int /*<<< orphan*/  flags; int /*<<< orphan*/ * fbops; TYPE_1__ fix; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMAP_MAX_SIZE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FBINFO_DEFAULT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* cfb ; 
 int /*<<< orphan*/  clps7111fb_ops ; 
 int /*<<< orphan*/  clps711x_guess_lcd_params (TYPE_2__*) ; 
 int /*<<< orphan*/  fb_alloc_cmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fb_get_options (char*,int /*<<< orphan*/ *) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int register_framebuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int clps711x_fb_probe(struct platform_device *pdev)
{
	int err = -ENOMEM;

	if (fb_get_options("clps711xfb", NULL))
		return -ENODEV;

	cfb = kzalloc(sizeof(*cfb), GFP_KERNEL);
	if (!cfb)
		goto out;

	strcpy(cfb->fix.id, "clps711x");

	cfb->fbops		= &clps7111fb_ops;
	cfb->flags		= FBINFO_DEFAULT;

	clps711x_guess_lcd_params(cfb);

	fb_alloc_cmap(&cfb->cmap, CMAP_MAX_SIZE, 0);

	err = register_framebuffer(cfb);

out:	return err;
}