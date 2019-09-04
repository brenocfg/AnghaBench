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
 int /*<<< orphan*/  put_tty_driver (struct tty_driver*) ; 
 int /*<<< orphan*/  tty_unregister_driver (struct tty_driver*) ; 

__attribute__((used)) static void dgnc_tty_free(struct tty_driver *drv)
{
	tty_unregister_driver(drv);
	put_tty_driver(drv);
}