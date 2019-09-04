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
struct list_head {int dummy; } ;
struct fb_videomode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 scalar_t__ fb_add_videomode (struct fb_videomode const*,struct list_head*) ; 

void fb_videomode_to_modelist(const struct fb_videomode *modedb, int num,
			      struct list_head *head)
{
	int i;

	INIT_LIST_HEAD(head);

	for (i = 0; i < num; i++) {
		if (fb_add_videomode(&modedb[i], head))
			return;
	}
}