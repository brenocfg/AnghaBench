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
struct imxfb_info {int num_modes; struct imx_fb_videomode const* mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  struct imx_fb_videomode {TYPE_1__ mode; } const imx_fb_videomode ;

/* Variables and functions */
 int /*<<< orphan*/  fb_mode ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct imx_fb_videomode *imxfb_find_mode(struct imxfb_info *fbi)
{
	struct imx_fb_videomode *m;
	int i;

	if (!fb_mode)
		return &fbi->mode[0];

	for (i = 0, m = &fbi->mode[0]; i < fbi->num_modes; i++, m++) {
		if (!strcmp(m->mode.name, fb_mode))
			return m;
	}
	return NULL;
}