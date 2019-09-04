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
struct wmi_delba_event {int /*<<< orphan*/  tid; } ;
struct wmi {int dummy; } ;
struct ath6kl_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aggr_recv_delba_req_evt (struct ath6kl_vif*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_wmi_delba_req_event_rx(struct wmi *wmi, u8 *datap, int len,
					 struct ath6kl_vif *vif)
{
	struct wmi_delba_event *cmd = (struct wmi_delba_event *) datap;

	aggr_recv_delba_req_evt(vif, cmd->tid);

	return 0;
}