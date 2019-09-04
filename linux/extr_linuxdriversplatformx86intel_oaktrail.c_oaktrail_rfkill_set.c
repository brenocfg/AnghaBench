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
typedef  unsigned long u8 ;

/* Variables and functions */
 int /*<<< orphan*/  OT_EC_DEVICE_STATE_ADDRESS ; 
 int /*<<< orphan*/  ec_read (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  ec_write (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int oaktrail_rfkill_set(void *data, bool blocked)
{
	u8 value;
	u8 result;
	unsigned long radio = (unsigned long) data;

	ec_read(OT_EC_DEVICE_STATE_ADDRESS, &result);

	if (!blocked)
		value = (u8) (result | radio);
	else
		value = (u8) (result & ~radio);

	ec_write(OT_EC_DEVICE_STATE_ADDRESS, value);

	return 0;
}