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
struct zfcp_fc_wka_port {int /*<<< orphan*/  mutex; int /*<<< orphan*/  status; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_FC_WKA_PORT_OFFLINE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zfcp_fc_wka_port_force_offline(struct zfcp_fc_wka_port *wka)
{
	cancel_delayed_work_sync(&wka->work);
	mutex_lock(&wka->mutex);
	wka->status = ZFCP_FC_WKA_PORT_OFFLINE;
	mutex_unlock(&wka->mutex);
}