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
 int /*<<< orphan*/ * gs_tty_driver ; 
 int /*<<< orphan*/  put_tty_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void userial_cleanup(void)
{
	tty_unregister_driver(gs_tty_driver);
	put_tty_driver(gs_tty_driver);
	gs_tty_driver = NULL;
}