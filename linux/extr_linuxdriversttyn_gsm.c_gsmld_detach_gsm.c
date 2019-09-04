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
struct gsm_mux {int num; struct tty_struct* tty; } ;

/* Variables and functions */
 int NUM_DLCI ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  gsm_cleanup_mux (struct gsm_mux*) ; 
 int /*<<< orphan*/  gsm_tty_driver ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gsmld_detach_gsm(struct tty_struct *tty, struct gsm_mux *gsm)
{
	int i;
	int base = gsm->num << 6; /* Base for this MUX */

	WARN_ON(tty != gsm->tty);
	for (i = 1; i < NUM_DLCI; i++)
		tty_unregister_device(gsm_tty_driver, base + i);
	gsm_cleanup_mux(gsm);
	tty_kref_put(gsm->tty);
	gsm->tty = NULL;
}