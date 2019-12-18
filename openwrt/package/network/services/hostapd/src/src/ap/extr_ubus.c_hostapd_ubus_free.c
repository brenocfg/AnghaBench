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
struct ubus_object {scalar_t__ id; scalar_t__ name; } ;
struct hapd_interfaces {struct ubus_object ubus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hostapd_ubus_ref_dec () ; 
 int /*<<< orphan*/  ubus_remove_object (int /*<<< orphan*/ ,struct ubus_object*) ; 

void hostapd_ubus_free(struct hapd_interfaces *interfaces)
{
	struct ubus_object *obj = &interfaces->ubus;
	char *name = (char *) obj->name;

	if (!ctx)
		return;

	if (obj->id) {
		ubus_remove_object(ctx, obj);
		hostapd_ubus_ref_dec();
	}

	free(name);
}