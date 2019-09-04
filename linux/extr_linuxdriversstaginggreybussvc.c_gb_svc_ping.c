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
struct gb_svc {int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int GB_OPERATION_TIMEOUT_DEFAULT ; 
 int /*<<< orphan*/  GB_SVC_TYPE_PING ; 
 int gb_operation_sync_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int gb_svc_ping(struct gb_svc *svc)
{
	return gb_operation_sync_timeout(svc->connection, GB_SVC_TYPE_PING,
					 NULL, 0, NULL, 0,
					 GB_OPERATION_TIMEOUT_DEFAULT * 2);
}