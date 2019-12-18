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
struct ubus_object {int /*<<< orphan*/  n_methods; int /*<<< orphan*/  methods; TYPE_1__* type; int /*<<< orphan*/  name; } ;
struct hapd_interfaces {char* name; struct ubus_object ubus; } ;
struct TYPE_2__ {int /*<<< orphan*/  n_methods; int /*<<< orphan*/  methods; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 TYPE_1__ daemon_object_type ; 
 int /*<<< orphan*/  hostapd_ubus_init () ; 
 int /*<<< orphan*/  hostapd_ubus_ref_inc () ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int ubus_add_object (int /*<<< orphan*/ ,struct ubus_object*) ; 

void hostapd_ubus_add(struct hapd_interfaces *interfaces)
{
	struct ubus_object *obj = &interfaces->ubus;
	int name_len;
	int ret;

	if (!hostapd_ubus_init())
		return;

	name_len = strlen("hostapd") + 1;
	if (interfaces->name)
		name_len += strlen(interfaces->name) + 1;
	obj->name = malloc(name_len);
	strcpy(obj->name, "hostapd");
	if (interfaces->name) {
		strcat(obj->name, ".");
		strcat(obj->name, interfaces->name);
	}

	obj->type = &daemon_object_type;
	obj->methods = daemon_object_type.methods;
	obj->n_methods = daemon_object_type.n_methods;
	ret = ubus_add_object(ctx, obj);
	hostapd_ubus_ref_inc();
}