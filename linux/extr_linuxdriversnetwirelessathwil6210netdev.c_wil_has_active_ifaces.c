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
struct wil6210_priv {int dummy; } ;

/* Variables and functions */
 int wil_has_other_active_ifaces (struct wil6210_priv*,int /*<<< orphan*/ *,int,int) ; 

bool wil_has_active_ifaces(struct wil6210_priv *wil, bool up, bool ok)
{
	/* use NULL ndev argument to check all interfaces */
	return wil_has_other_active_ifaces(wil, NULL, up, ok);
}