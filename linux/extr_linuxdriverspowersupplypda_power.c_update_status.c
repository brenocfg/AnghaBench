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
struct TYPE_2__ {int /*<<< orphan*/  (* is_usb_online ) () ;int /*<<< orphan*/  (* is_ac_online ) () ;} ;

/* Variables and functions */
 int new_ac_status ; 
 int new_usb_status ; 
 TYPE_1__* pdata ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static void update_status(void)
{
	if (pdata->is_ac_online)
		new_ac_status = !!pdata->is_ac_online();

	if (pdata->is_usb_online)
		new_usb_status = !!pdata->is_usb_online();
}