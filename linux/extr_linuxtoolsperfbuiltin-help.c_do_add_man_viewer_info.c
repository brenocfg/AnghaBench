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
struct man_viewer_info_list {struct man_viewer_info_list* next; int /*<<< orphan*/  info; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct man_viewer_info_list* man_viewer_info_list ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 struct man_viewer_info_list* zalloc (int) ; 

__attribute__((used)) static void do_add_man_viewer_info(const char *name,
				   size_t len,
				   const char *value)
{
	struct man_viewer_info_list *new = zalloc(sizeof(*new) + len + 1);

	strncpy(new->name, name, len);
	new->info = strdup(value);
	new->next = man_viewer_info_list;
	man_viewer_info_list = new;
}