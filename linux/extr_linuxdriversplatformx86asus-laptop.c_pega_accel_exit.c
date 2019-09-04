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
struct asus_laptop {int /*<<< orphan*/ * pega_accel_poll; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_free_polled_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_polled_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pega_accel_exit(struct asus_laptop *asus)
{
	if (asus->pega_accel_poll) {
		input_unregister_polled_device(asus->pega_accel_poll);
		input_free_polled_device(asus->pega_accel_poll);
	}
	asus->pega_accel_poll = NULL;
}