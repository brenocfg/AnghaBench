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
struct tty_struct {struct gsm_dlci* driver_data; } ;
struct gsm_dlci {scalar_t__ state; int /*<<< orphan*/  port; int /*<<< orphan*/  mutex; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ C_HUPCL (struct tty_struct*) ; 
 scalar_t__ DLCI_CLOSED ; 
 int /*<<< orphan*/  gsm_destroy_network (struct gsm_dlci*) ; 
 int /*<<< orphan*/  gsm_dlci_begin_close (struct gsm_dlci*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_close_end (int /*<<< orphan*/ *,struct tty_struct*) ; 
 scalar_t__ tty_port_close_start (int /*<<< orphan*/ *,struct tty_struct*,struct file*) ; 
 scalar_t__ tty_port_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_lower_dtr_rts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_tty_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gsmtty_close(struct tty_struct *tty, struct file *filp)
{
	struct gsm_dlci *dlci = tty->driver_data;

	if (dlci == NULL)
		return;
	if (dlci->state == DLCI_CLOSED)
		return;
	mutex_lock(&dlci->mutex);
	gsm_destroy_network(dlci);
	mutex_unlock(&dlci->mutex);
	if (tty_port_close_start(&dlci->port, tty, filp) == 0)
		return;
	gsm_dlci_begin_close(dlci);
	if (tty_port_initialized(&dlci->port) && C_HUPCL(tty))
		tty_port_lower_dtr_rts(&dlci->port);
	tty_port_close_end(&dlci->port, tty);
	tty_port_tty_set(&dlci->port, NULL);
	return;
}