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
struct wil6210_vif {int dummy; } ;
struct wil6210_priv {int /*<<< orphan*/  status; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wil6210_vif* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_timer ; 
 struct wil6210_vif* vif ; 
 struct wil6210_priv* vif_to_wil (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_fw_error_recovery (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_status_fwready ; 

__attribute__((used)) static void wil_scan_timer_fn(struct timer_list *t)
{
	struct wil6210_vif *vif = from_timer(vif, t, scan_timer);
	struct wil6210_priv *wil = vif_to_wil(vif);

	clear_bit(wil_status_fwready, wil->status);
	wil_err(wil, "Scan timeout detected, start fw error recovery\n");
	wil_fw_error_recovery(wil);
}