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
struct consw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  do_unregister_con_driver (struct consw const*) ; 

void give_up_console(const struct consw *csw)
{
	console_lock();
	do_unregister_con_driver(csw);
	console_unlock();
}