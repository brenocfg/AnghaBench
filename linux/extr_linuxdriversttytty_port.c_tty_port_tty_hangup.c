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
struct tty_struct {int dummy; } ;
struct tty_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_CLOCAL (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_hangup (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (struct tty_port*) ; 

void tty_port_tty_hangup(struct tty_port *port, bool check_clocal)
{
	struct tty_struct *tty = tty_port_tty_get(port);

	if (tty && (!check_clocal || !C_CLOCAL(tty)))
		tty_hangup(tty);
	tty_kref_put(tty);
}