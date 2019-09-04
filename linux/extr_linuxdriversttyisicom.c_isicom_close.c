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
struct tty_struct {int /*<<< orphan*/  name; struct isi_port* driver_data; } ;
struct tty_port {int dummy; } ;
struct isi_port {struct tty_port port; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ isicom_paranoia_check (struct isi_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tty_port_close (struct tty_port*,struct tty_struct*,struct file*) ; 

__attribute__((used)) static void isicom_close(struct tty_struct *tty, struct file *filp)
{
	struct isi_port *ip = tty->driver_data;
	struct tty_port *port;

	if (ip == NULL)
		return;

	port = &ip->port;
	if (isicom_paranoia_check(ip, tty->name, "isicom_close"))
		return;
	tty_port_close(port, tty, filp);
}