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
struct kobject {int dummy; } ;
struct batadv_priv {TYPE_2__* soft_iface; } ;
typedef  enum batadv_uev_type { ____Placeholder_batadv_uev_type } batadv_uev_type ;
typedef  enum batadv_uev_action { ____Placeholder_batadv_uev_action } batadv_uev_action ;
struct TYPE_3__ {struct kobject kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_BATMAN ; 
 int /*<<< orphan*/  BATADV_UEV_ACTION_VAR ; 
 int /*<<< orphan*/  BATADV_UEV_DATA_VAR ; 
 int BATADV_UEV_DEL ; 
 int /*<<< orphan*/  BATADV_UEV_TYPE_VAR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,char const*,char const*,char*,int) ; 
 char const** batadv_uev_action_str ; 
 char const** batadv_uev_type_str ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int kobject_uevent_env (struct kobject*,int /*<<< orphan*/ ,char**) ; 

int batadv_throw_uevent(struct batadv_priv *bat_priv, enum batadv_uev_type type,
			enum batadv_uev_action action, const char *data)
{
	int ret = -ENOMEM;
	struct kobject *bat_kobj;
	char *uevent_env[4] = { NULL, NULL, NULL, NULL };

	bat_kobj = &bat_priv->soft_iface->dev.kobj;

	uevent_env[0] = kasprintf(GFP_ATOMIC,
				  "%s%s", BATADV_UEV_TYPE_VAR,
				  batadv_uev_type_str[type]);
	if (!uevent_env[0])
		goto out;

	uevent_env[1] = kasprintf(GFP_ATOMIC,
				  "%s%s", BATADV_UEV_ACTION_VAR,
				  batadv_uev_action_str[action]);
	if (!uevent_env[1])
		goto out;

	/* If the event is DEL, ignore the data field */
	if (action != BATADV_UEV_DEL) {
		uevent_env[2] = kasprintf(GFP_ATOMIC,
					  "%s%s", BATADV_UEV_DATA_VAR, data);
		if (!uevent_env[2])
			goto out;
	}

	ret = kobject_uevent_env(bat_kobj, KOBJ_CHANGE, uevent_env);
out:
	kfree(uevent_env[0]);
	kfree(uevent_env[1]);
	kfree(uevent_env[2]);

	if (ret)
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Impossible to send uevent for (%s,%s,%s) event (err: %d)\n",
			   batadv_uev_type_str[type],
			   batadv_uev_action_str[action],
			   (action == BATADV_UEV_DEL ? "NULL" : data), ret);
	return ret;
}