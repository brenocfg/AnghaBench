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
struct tty_struct {int count; int /*<<< orphan*/  port; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  tty_port_close (int /*<<< orphan*/ ,struct tty_struct*,struct file*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void vcc_close(struct tty_struct *tty, struct file *vcc_file)
{
	if (unlikely(!tty)) {
		pr_err("VCC: close: Invalid TTY handle\n");
		return;
	}

	if (unlikely(tty->count > 1))
		return;

	if (unlikely(!tty->port)) {
		pr_err("VCC: close: TTY port not found\n");
		return;
	}

	tty_port_close(tty->port, tty, vcc_file);
}