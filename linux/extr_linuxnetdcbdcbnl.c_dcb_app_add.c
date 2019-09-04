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
struct dcb_app_type {int ifindex; int /*<<< orphan*/  list; int /*<<< orphan*/  app; } ;
struct dcb_app {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dcb_app_list ; 
 struct dcb_app_type* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dcb_app const*,int) ; 

__attribute__((used)) static int dcb_app_add(const struct dcb_app *app, int ifindex)
{
	struct dcb_app_type *entry;

	entry = kmalloc(sizeof(*entry), GFP_ATOMIC);
	if (!entry)
		return -ENOMEM;

	memcpy(&entry->app, app, sizeof(*app));
	entry->ifindex = ifindex;
	list_add(&entry->list, &dcb_app_list);

	return 0;
}