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
struct TYPE_2__ {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  io_addr; int /*<<< orphan*/  supports_temp; scalar_t__ command_mode; } ;

/* Variables and functions */
 scalar_t__ DEBUG ; 
 int ENODEV ; 
 scalar_t__ debug ; 
 int inb (int /*<<< orphan*/ ) ; 
 TYPE_1__ pcwd_private ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcwd_get_temperature(int *temperature)
{
	/* check that port 0 gives temperature info and no command results */
	if (pcwd_private.command_mode)
		return -1;

	*temperature = 0;
	if (!pcwd_private.supports_temp)
		return -ENODEV;

	/*
	 * Convert celsius to fahrenheit, since this was
	 * the decided 'standard' for this return value.
	 */
	spin_lock(&pcwd_private.io_lock);
	*temperature = ((inb(pcwd_private.io_addr)) * 9 / 5) + 32;
	spin_unlock(&pcwd_private.io_lock);

	if (debug >= DEBUG) {
		pr_debug("temperature is: %d F\n", *temperature);
	}

	return 0;
}