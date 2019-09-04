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
 int /*<<< orphan*/  MSI_STANDARD_EC_3G_MASK ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int set_device_state (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rfkill_threeg_set(void *data, bool blocked)
{
	int result = set_device_state(blocked ? "0" : "1", 0,
			MSI_STANDARD_EC_3G_MASK);

	return min(result, 0);
}