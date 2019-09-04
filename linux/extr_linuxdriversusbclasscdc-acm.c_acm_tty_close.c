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
struct tty_struct {struct acm* driver_data; } ;
struct file {int dummy; } ;
struct acm {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_port_close (int /*<<< orphan*/ *,struct tty_struct*,struct file*) ; 

__attribute__((used)) static void acm_tty_close(struct tty_struct *tty, struct file *filp)
{
	struct acm *acm = tty->driver_data;

	tty_port_close(&acm->port, tty, filp);
}