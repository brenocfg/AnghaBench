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

/* Variables and functions */
 int sony_call_snc_handle (int /*<<< orphan*/ ,int,int*) ; 
 int* sony_rfkill_address ; 
 int /*<<< orphan*/  sony_rfkill_handle ; 

__attribute__((used)) static int sony_nc_rfkill_set(void *data, bool blocked)
{
	int result;
	int argument = sony_rfkill_address[(long) data] + 0x100;

	if (!blocked)
		argument |= 0x070000;

	return sony_call_snc_handle(sony_rfkill_handle, argument, &result);
}