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
struct linux_logo {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static const struct linux_logo *newport_show_logo(void)
{
#ifdef CONFIG_LOGO_SGI_CLUT224
	const struct linux_logo *logo = fb_find_logo(8);
	const unsigned char *clut;
	const unsigned char *data;
	unsigned long i;

	if (!logo)
		return NULL;
	clut = logo->clut;
	data = logo->data;

	for (i = 0; i < logo->clutsize; i++) {
		newport_bfwait(npregs);
		newport_cmap_setaddr(npregs, i + 0x20);
		newport_cmap_setrgb(npregs, clut[0], clut[1], clut[2]);
		clut += 3;
	}

	newport_wait(npregs);
	npregs->set.drawmode0 = (NPORT_DMODE0_DRAW | NPORT_DMODE0_BLOCK |
				 NPORT_DMODE0_CHOST);

	npregs->set.xystarti = ((newport_xsize - logo->width) << 16) | (0);
	npregs->set.xyendi = ((newport_xsize - 1) << 16);
	newport_wait(npregs);

	for (i = 0; i < logo->width*logo->height; i++)
		npregs->go.hostrw0 = *data++ << 24;

	return logo;
#endif /* CONFIG_LOGO_SGI_CLUT224 */
}