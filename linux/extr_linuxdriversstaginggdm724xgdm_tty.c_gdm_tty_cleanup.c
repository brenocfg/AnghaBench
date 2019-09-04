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
struct tty_struct {struct gdm* driver_data; } ;
struct gdm {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_port_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gdm_tty_cleanup(struct tty_struct *tty)
{
	struct gdm *gdm = tty->driver_data;

	tty_port_put(&gdm->port);
}