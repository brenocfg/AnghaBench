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
struct _adapter {int /*<<< orphan*/  pnetdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_indicate_wx_assoc_event (struct _adapter*) ; 

void r8712_os_indicate_connect(struct _adapter *adapter)
{
	r8712_indicate_wx_assoc_event(adapter);
	netif_carrier_on(adapter->pnetdev);
}