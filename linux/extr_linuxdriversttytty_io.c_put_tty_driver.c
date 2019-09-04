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
struct tty_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_driver_kref_put (struct tty_driver*) ; 

void put_tty_driver(struct tty_driver *d)
{
	tty_driver_kref_put(d);
}