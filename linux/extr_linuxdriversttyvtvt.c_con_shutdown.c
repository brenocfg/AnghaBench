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
struct TYPE_2__ {int /*<<< orphan*/ * tty; } ;
struct vc_data {TYPE_1__ port; } ;
struct tty_struct {struct vc_data* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 

__attribute__((used)) static void con_shutdown(struct tty_struct *tty)
{
	struct vc_data *vc = tty->driver_data;
	BUG_ON(vc == NULL);
	console_lock();
	vc->port.tty = NULL;
	console_unlock();
}