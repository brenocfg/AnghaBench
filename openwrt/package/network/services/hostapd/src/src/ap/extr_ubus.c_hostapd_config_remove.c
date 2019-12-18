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
struct ubus_request_data {int dummy; } ;
struct ubus_object {int dummy; } ;
struct ubus_context {int dummy; } ;
struct hapd_interfaces {int dummy; } ;
struct blob_attr {int dummy; } ;

/* Variables and functions */
 size_t CONFIG_REM_IFACE ; 
 int UBUS_STATUS_INVALID_ARGUMENT ; 
 int UBUS_STATUS_OK ; 
 int __CONFIG_REM_MAX ; 
 int /*<<< orphan*/  blob_data (struct blob_attr*) ; 
 int /*<<< orphan*/  blob_len (struct blob_attr*) ; 
 int /*<<< orphan*/  blobmsg_get_string (struct blob_attr*) ; 
 int /*<<< orphan*/  blobmsg_parse (int /*<<< orphan*/ ,int,struct blob_attr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_remove_policy ; 
 struct hapd_interfaces* get_hapd_interfaces_from_object (struct ubus_object*) ; 
 scalar_t__ hostapd_remove_iface (struct hapd_interfaces*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hostapd_config_remove(struct ubus_context *ctx, struct ubus_object *obj,
		      struct ubus_request_data *req, const char *method,
		      struct blob_attr *msg)
{
	struct blob_attr *tb[__CONFIG_REM_MAX];
	struct hapd_interfaces *interfaces = get_hapd_interfaces_from_object(obj);
	char buf[128];

	blobmsg_parse(config_remove_policy, __CONFIG_REM_MAX, tb, blob_data(msg), blob_len(msg));

	if (!tb[CONFIG_REM_IFACE])
		return UBUS_STATUS_INVALID_ARGUMENT;

	if (hostapd_remove_iface(interfaces, blobmsg_get_string(tb[CONFIG_REM_IFACE])))
		return UBUS_STATUS_INVALID_ARGUMENT;

	return UBUS_STATUS_OK;
}