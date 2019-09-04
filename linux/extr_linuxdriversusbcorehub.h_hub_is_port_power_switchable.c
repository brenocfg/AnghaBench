#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_hub {TYPE_1__* descriptor; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  wHubCharacteristics; } ;

/* Variables and functions */
 int HUB_CHAR_LPSM ; 
 int HUB_CHAR_NO_LPSM ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool hub_is_port_power_switchable(struct usb_hub *hub)
{
	__le16 hcs;

	if (!hub)
		return false;
	hcs = hub->descriptor->wHubCharacteristics;
	return (le16_to_cpu(hcs) & HUB_CHAR_LPSM) < HUB_CHAR_NO_LPSM;
}