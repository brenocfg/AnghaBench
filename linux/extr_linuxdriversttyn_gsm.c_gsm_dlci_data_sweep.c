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
struct gsm_mux {scalar_t__ tx_bytes; struct gsm_dlci** dlci; } ;
struct gsm_dlci {int adaption; int /*<<< orphan*/  net; scalar_t__ constipated; } ;

/* Variables and functions */
 int NUM_DLCI ; 
 scalar_t__ TX_THRESH_HI ; 
 int gsm_dlci_data_output (struct gsm_mux*,struct gsm_dlci*) ; 
 int gsm_dlci_data_output_framed (struct gsm_mux*,struct gsm_dlci*) ; 

__attribute__((used)) static void gsm_dlci_data_sweep(struct gsm_mux *gsm)
{
	int len;
	/* Priority ordering: We should do priority with RR of the groups */
	int i = 1;

	while (i < NUM_DLCI) {
		struct gsm_dlci *dlci;

		if (gsm->tx_bytes > TX_THRESH_HI)
			break;
		dlci = gsm->dlci[i];
		if (dlci == NULL || dlci->constipated) {
			i++;
			continue;
		}
		if (dlci->adaption < 3 && !dlci->net)
			len = gsm_dlci_data_output(gsm, dlci);
		else
			len = gsm_dlci_data_output_framed(gsm, dlci);
		if (len < 0)
			break;
		/* DLCI empty - try the next */
		if (len == 0)
			i++;
	}
}