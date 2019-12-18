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
struct ubus_banned_client {int /*<<< orphan*/  avl; } ;
struct TYPE_2__ {int /*<<< orphan*/  banned; } ;
struct hostapd_data {TYPE_1__ ubus; } ;

/* Variables and functions */
 int /*<<< orphan*/  avl_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ubus_banned_client*) ; 

__attribute__((used)) static void
hostapd_bss_del_ban(void *eloop_data, void *user_ctx)
{
	struct ubus_banned_client *ban = eloop_data;
	struct hostapd_data *hapd = user_ctx;

	avl_delete(&hapd->ubus.banned, &ban->avl);
	free(ban);
}