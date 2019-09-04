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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wmi_rcp_delba_cmd {int cidxtid; int /*<<< orphan*/  reason; } ;
struct wil6210_priv {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_RCP_DELBA_CMDID ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_dbg_wmi (struct wil6210_priv*,char*,int,int,int /*<<< orphan*/ ) ; 
 int wmi_send (struct wil6210_priv*,int /*<<< orphan*/ ,int,struct wmi_rcp_delba_cmd*,int) ; 

int wmi_delba_rx(struct wil6210_priv *wil, u8 mid, u8 cidxtid, u16 reason)
{
	struct wmi_rcp_delba_cmd cmd = {
		.cidxtid = cidxtid,
		.reason = cpu_to_le16(reason),
	};

	wil_dbg_wmi(wil, "delba_rx: (CID %d TID %d reason %d)\n", cidxtid & 0xf,
		    (cidxtid >> 4) & 0xf, reason);

	return wmi_send(wil, WMI_RCP_DELBA_CMDID, mid, &cmd, sizeof(cmd));
}