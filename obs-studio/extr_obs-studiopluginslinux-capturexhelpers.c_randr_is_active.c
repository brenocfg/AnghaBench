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
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_2__ {int /*<<< orphan*/  present; } ;

/* Variables and functions */
 TYPE_1__* xcb_get_extension_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_randr_id ; 

bool randr_is_active(xcb_connection_t *xcb)
{
	if (!xcb || !xcb_get_extension_data(xcb, &xcb_randr_id)->present)
		return false;

	return true;
}