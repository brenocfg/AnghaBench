#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; } ;
struct ubus_object {int /*<<< orphan*/  n_methods; int /*<<< orphan*/  methods; TYPE_2__* type; int /*<<< orphan*/  name; } ;
struct wpa_global {TYPE_1__ params; struct ubus_object ubus_global; } ;
struct TYPE_4__ {int /*<<< orphan*/  n_methods; int /*<<< orphan*/  methods; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int ubus_add_object (int /*<<< orphan*/ ,struct ubus_object*) ; 
 TYPE_2__ wpas_daemon_object_type ; 
 int /*<<< orphan*/  wpas_ubus_init () ; 
 int /*<<< orphan*/  wpas_ubus_ref_inc () ; 

void wpas_ubus_add(struct wpa_global *global)
{
	struct ubus_object *obj = &global->ubus_global;
	int name_len;
	int ret;

	if (!wpas_ubus_init())
		return;

	name_len = strlen("wpa_supplicant") + 1;
	if (global->params.name)
		name_len += strlen(global->params.name) + 1;
	obj->name = malloc(name_len);
	strcpy(obj->name, "wpa_supplicant");

	if (global->params.name)
	{
		strcat(obj->name, ".");
		strcat(obj->name, global->params.name);
	}

	obj->type = &wpas_daemon_object_type;
	obj->methods = wpas_daemon_object_type.methods;
	obj->n_methods = wpas_daemon_object_type.n_methods;
	ret = ubus_add_object(ctx, obj);
	wpas_ubus_ref_inc();
}