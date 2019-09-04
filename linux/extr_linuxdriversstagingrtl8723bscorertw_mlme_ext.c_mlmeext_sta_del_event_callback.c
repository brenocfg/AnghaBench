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
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_IBSS_empty (struct adapter*) ; 
 scalar_t__ is_client_associated_to_ap (struct adapter*) ; 
 int /*<<< orphan*/  rtw_mlmeext_disconnect (struct adapter*) ; 

void mlmeext_sta_del_event_callback(struct adapter *padapter)
{
	if (is_client_associated_to_ap(padapter) || is_IBSS_empty(padapter))
		rtw_mlmeext_disconnect(padapter);
}