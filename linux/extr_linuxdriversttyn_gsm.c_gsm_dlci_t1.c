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
struct timer_list {int dummy; } ;
struct gsm_mux {int t1; int control; } ;
struct gsm_dlci {int state; int /*<<< orphan*/  t1; int /*<<< orphan*/  addr; struct gsm_mux* gsm; int /*<<< orphan*/  retries; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int DISC ; 
#define  DLCI_CLOSING 129 
 int /*<<< orphan*/  DLCI_MODE_ADM ; 
#define  DLCI_OPENING 128 
 int DM ; 
 int HZ ; 
 int PF ; 
 int SABM ; 
 int debug ; 
 struct gsm_dlci* dlci ; 
 struct gsm_dlci* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsm_command (struct gsm_mux*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gsm_dlci_close (struct gsm_dlci*) ; 
 int /*<<< orphan*/  gsm_dlci_open (struct gsm_dlci*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1 ; 

__attribute__((used)) static void gsm_dlci_t1(struct timer_list *t)
{
	struct gsm_dlci *dlci = from_timer(dlci, t, t1);
	struct gsm_mux *gsm = dlci->gsm;

	switch (dlci->state) {
	case DLCI_OPENING:
		dlci->retries--;
		if (dlci->retries) {
			gsm_command(dlci->gsm, dlci->addr, SABM|PF);
			mod_timer(&dlci->t1, jiffies + gsm->t1 * HZ / 100);
		} else if (!dlci->addr && gsm->control == (DM | PF)) {
			if (debug & 8)
				pr_info("DLCI %d opening in ADM mode.\n",
					dlci->addr);
			dlci->mode = DLCI_MODE_ADM;
			gsm_dlci_open(dlci);
		} else {
			gsm_dlci_close(dlci);
		}

		break;
	case DLCI_CLOSING:
		dlci->retries--;
		if (dlci->retries) {
			gsm_command(dlci->gsm, dlci->addr, DISC|PF);
			mod_timer(&dlci->t1, jiffies + gsm->t1 * HZ / 100);
		} else
			gsm_dlci_close(dlci);
		break;
	}
}