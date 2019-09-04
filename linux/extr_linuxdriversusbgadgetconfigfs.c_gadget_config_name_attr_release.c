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
struct gadget_config_name {int /*<<< orphan*/  list; struct gadget_config_name* configuration; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct gadget_config_name*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct gadget_config_name* to_gadget_config_name (struct config_item*) ; 

__attribute__((used)) static void gadget_config_name_attr_release(struct config_item *item)
{
	struct gadget_config_name *cn = to_gadget_config_name(item);

	kfree(cn->configuration);

	list_del(&cn->list);
	kfree(cn);
}