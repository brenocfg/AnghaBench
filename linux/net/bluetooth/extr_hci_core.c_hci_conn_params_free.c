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
struct hci_conn_params {int /*<<< orphan*/  list; int /*<<< orphan*/  action; scalar_t__ conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  hci_conn_drop (scalar_t__) ; 
 int /*<<< orphan*/  hci_conn_put (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct hci_conn_params*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_conn_params_free(struct hci_conn_params *params)
{
	if (params->conn) {
		hci_conn_drop(params->conn);
		hci_conn_put(params->conn);
	}

	list_del(&params->action);
	list_del(&params->list);
	kfree(params);
}