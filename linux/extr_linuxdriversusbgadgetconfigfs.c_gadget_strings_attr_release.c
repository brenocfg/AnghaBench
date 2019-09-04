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
struct gadget_strings {int /*<<< orphan*/  list; struct gadget_strings* serialnumber; struct gadget_strings* product; struct gadget_strings* manufacturer; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct gadget_strings*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct gadget_strings* to_gadget_strings (struct config_item*) ; 

__attribute__((used)) static void gadget_strings_attr_release(struct config_item *item)
{
	struct gadget_strings *gs = to_gadget_strings(item);

	kfree(gs->manufacturer);
	kfree(gs->product);
	kfree(gs->serialnumber);

	list_del(&gs->list);
	kfree(gs);
}