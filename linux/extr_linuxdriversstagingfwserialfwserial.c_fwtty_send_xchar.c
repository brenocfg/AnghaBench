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
struct tty_struct {struct fwtty_port* driver_data; } ;
struct fwtty_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwtty_dbg (struct fwtty_port*,char*,char) ; 
 int /*<<< orphan*/  fwtty_write_xchar (struct fwtty_port*,char) ; 

__attribute__((used)) static void fwtty_send_xchar(struct tty_struct *tty, char ch)
{
	struct fwtty_port *port = tty->driver_data;

	fwtty_dbg(port, "%02x\n", ch);

	fwtty_write_xchar(port, ch);
}