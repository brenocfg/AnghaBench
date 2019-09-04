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
struct wlan_network {int dummy; } ;
struct mlme_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtw_free_network_nolock (struct mlme_priv*,struct wlan_network*) ; 

__attribute__((used)) static void rtw_free_network_nolock(struct mlme_priv *pmlmepriv,
				    struct wlan_network *pnetwork)
{
	_rtw_free_network_nolock(pmlmepriv, pnetwork);
}