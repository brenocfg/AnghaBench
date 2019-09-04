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
struct gsm_mux {int t1; int /*<<< orphan*/  n2; } ;
struct gsm_dlci {scalar_t__ state; int /*<<< orphan*/  t1; int /*<<< orphan*/  addr; struct gsm_mux* gsm; int /*<<< orphan*/  retries; } ;

/* Variables and functions */
 scalar_t__ DLCI_OPEN ; 
 scalar_t__ DLCI_OPENING ; 
 int HZ ; 
 int PF ; 
 int SABM ; 
 int /*<<< orphan*/  gsm_command (struct gsm_mux*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void gsm_dlci_begin_open(struct gsm_dlci *dlci)
{
	struct gsm_mux *gsm = dlci->gsm;
	if (dlci->state == DLCI_OPEN || dlci->state == DLCI_OPENING)
		return;
	dlci->retries = gsm->n2;
	dlci->state = DLCI_OPENING;
	gsm_command(dlci->gsm, dlci->addr, SABM|PF);
	mod_timer(&dlci->t1, jiffies + gsm->t1 * HZ / 100);
}