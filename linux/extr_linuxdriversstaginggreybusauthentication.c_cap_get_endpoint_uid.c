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
typedef  int /*<<< orphan*/  u8 ;
struct gb_connection {int dummy; } ;
struct gb_cap_get_endpoint_uid_response {int /*<<< orphan*/  uid; } ;
struct gb_cap {int /*<<< orphan*/  parent; struct gb_connection* connection; } ;
typedef  int /*<<< orphan*/  response ;

/* Variables and functions */
 int /*<<< orphan*/  GB_CAP_TYPE_GET_ENDPOINT_UID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int gb_operation_sync (struct gb_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gb_cap_get_endpoint_uid_response*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cap_get_endpoint_uid(struct gb_cap *cap, u8 *euid)
{
	struct gb_connection *connection = cap->connection;
	struct gb_cap_get_endpoint_uid_response response;
	int ret;

	ret = gb_operation_sync(connection, GB_CAP_TYPE_GET_ENDPOINT_UID, NULL,
				0, &response, sizeof(response));
	if (ret) {
		dev_err(cap->parent, "failed to get endpoint uid (%d)\n", ret);
		return ret;
	}

	memcpy(euid, response.uid, sizeof(response.uid));

	return 0;
}