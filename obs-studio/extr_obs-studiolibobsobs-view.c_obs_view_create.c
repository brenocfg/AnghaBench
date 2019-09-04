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
struct obs_view {int dummy; } ;
typedef  struct obs_view obs_view_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct obs_view*) ; 
 struct obs_view* bzalloc (int) ; 
 int /*<<< orphan*/  obs_view_init (struct obs_view*) ; 

obs_view_t *obs_view_create(void)
{
	struct obs_view *view = bzalloc(sizeof(struct obs_view));

	if (!obs_view_init(view)) {
		bfree(view);
		view = NULL;
	}

	return view;
}