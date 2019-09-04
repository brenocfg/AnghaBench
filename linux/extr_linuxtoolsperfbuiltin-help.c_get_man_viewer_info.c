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
struct man_viewer_info_list {char const* info; int /*<<< orphan*/  name; struct man_viewer_info_list* next; } ;

/* Variables and functions */
 struct man_viewer_info_list* man_viewer_info_list ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *get_man_viewer_info(const char *name)
{
	struct man_viewer_info_list *viewer;

	for (viewer = man_viewer_info_list; viewer; viewer = viewer->next) {
		if (!strcasecmp(name, viewer->name))
			return viewer->info;
	}
	return NULL;
}