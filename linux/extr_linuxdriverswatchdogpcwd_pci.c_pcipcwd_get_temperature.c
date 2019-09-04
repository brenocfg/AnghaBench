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
struct TYPE_2__ {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  io_addr; int /*<<< orphan*/  supports_temp; } ;

/* Variables and functions */
 scalar_t__ DEBUG ; 
 int ENODEV ; 
 scalar_t__ debug ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 TYPE_1__ pcipcwd_private ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcipcwd_get_temperature(int *temperature)
{
	*temperature = 0;
	if (!pcipcwd_private.supports_temp)
		return -ENODEV;

	spin_lock(&pcipcwd_private.io_lock);
	*temperature = inb_p(pcipcwd_private.io_addr);
	spin_unlock(&pcipcwd_private.io_lock);

	/*
	 * Convert celsius to fahrenheit, since this was
	 * the decided 'standard' for this return value.
	 */
	*temperature = (*temperature * 9 / 5) + 32;

	if (debug >= DEBUG) {
		pr_debug("temperature is: %d F\n", *temperature);
	}

	return 0;
}