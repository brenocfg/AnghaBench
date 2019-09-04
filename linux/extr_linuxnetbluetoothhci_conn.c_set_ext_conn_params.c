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
struct hci_dev {int le_scan_interval; } ;
struct hci_cp_le_ext_conn_param {void* max_ce_len; void* min_ce_len; void* supervision_timeout; void* conn_latency; void* conn_interval_max; void* conn_interval_min; void* scan_interval; void* scan_window; } ;
struct hci_conn {int le_conn_min_interval; int le_conn_max_interval; int le_conn_latency; int le_supv_timeout; struct hci_dev* hdev; } ;

/* Variables and functions */
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (struct hci_cp_le_ext_conn_param*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_ext_conn_params(struct hci_conn *conn,
				struct hci_cp_le_ext_conn_param *p)
{
	struct hci_dev *hdev = conn->hdev;

	memset(p, 0, sizeof(*p));

	/* Set window to be the same value as the interval to
	 * enable continuous scanning.
	 */
	p->scan_interval = cpu_to_le16(hdev->le_scan_interval);
	p->scan_window = p->scan_interval;
	p->conn_interval_min = cpu_to_le16(conn->le_conn_min_interval);
	p->conn_interval_max = cpu_to_le16(conn->le_conn_max_interval);
	p->conn_latency = cpu_to_le16(conn->le_conn_latency);
	p->supervision_timeout = cpu_to_le16(conn->le_supv_timeout);
	p->min_ce_len = cpu_to_le16(0x0000);
	p->max_ce_len = cpu_to_le16(0x0000);
}