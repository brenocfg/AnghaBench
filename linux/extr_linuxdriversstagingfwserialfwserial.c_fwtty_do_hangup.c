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
struct work_struct {int dummy; } ;
struct tty_struct {int dummy; } ;
struct fwtty_port {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  hangup ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int /*<<< orphan*/ ) ; 
 struct fwtty_port* to_port (struct work_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_vhangup (struct tty_struct*) ; 

__attribute__((used)) static void fwtty_do_hangup(struct work_struct *work)
{
	struct fwtty_port *port = to_port(work, hangup);
	struct tty_struct *tty;

	schedule_timeout_uninterruptible(msecs_to_jiffies(50));

	tty = tty_port_tty_get(&port->port);
	if (tty)
		tty_vhangup(tty);
	tty_kref_put(tty);
}