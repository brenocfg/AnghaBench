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
struct gsm_mux {struct gsm_dlci** dlci; } ;
struct gsm_dlci {struct gsm_mux* gsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlci_put (struct gsm_dlci*) ; 
 int /*<<< orphan*/  mux_put (struct gsm_mux*) ; 

__attribute__((used)) static void gsmtty_cleanup(struct tty_struct *tty)
{
	struct gsm_dlci *dlci = tty->driver_data;
	struct gsm_mux *gsm = dlci->gsm;

	dlci_put(dlci);
	dlci_put(gsm->dlci[0]);
	mux_put(gsm);
}