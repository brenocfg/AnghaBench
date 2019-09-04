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
struct TYPE_2__ {int /*<<< orphan*/  cmap; } ;
struct cfb_info {TYPE_1__ fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_alloc_cmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cfb_info*) ; 

__attribute__((used)) static void cyberpro_free_fb_info(struct cfb_info *cfb)
{
	if (cfb) {
		/*
		 * Free the colourmap
		 */
		fb_alloc_cmap(&cfb->fb.cmap, 0, 0);

		kfree(cfb);
	}
}