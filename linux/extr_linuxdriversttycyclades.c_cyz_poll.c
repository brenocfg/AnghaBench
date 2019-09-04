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
struct cyclades_port {int /*<<< orphan*/  throttle; } ;
struct cyclades_card {int intr_enabled; unsigned int nports; struct cyclades_port* ports; } ;

/* Variables and functions */
 unsigned long HZ ; 
 unsigned int NR_CARDS ; 
 struct cyclades_card* cy_card ; 
 int /*<<< orphan*/  cy_is_Z (struct cyclades_card*) ; 
 int /*<<< orphan*/  cyz_handle_cmd (struct cyclades_card*) ; 
 int /*<<< orphan*/  cyz_handle_rx (struct cyclades_port*) ; 
 int /*<<< orphan*/  cyz_handle_tx (struct cyclades_port*) ; 
 int /*<<< orphan*/  cyz_is_loaded (struct cyclades_card*) ; 
 unsigned long cyz_polling_cycle ; 
 int /*<<< orphan*/  cyz_timerlist ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cyz_poll(struct timer_list *unused)
{
	struct cyclades_card *cinfo;
	struct cyclades_port *info;
	unsigned long expires = jiffies + HZ;
	unsigned int port, card;

	for (card = 0; card < NR_CARDS; card++) {
		cinfo = &cy_card[card];

		if (!cy_is_Z(cinfo))
			continue;
		if (!cyz_is_loaded(cinfo))
			continue;

	/* Skip first polling cycle to avoid racing conditions with the FW */
		if (!cinfo->intr_enabled) {
			cinfo->intr_enabled = 1;
			continue;
		}

		cyz_handle_cmd(cinfo);

		for (port = 0; port < cinfo->nports; port++) {
			info = &cinfo->ports[port];

			if (!info->throttle)
				cyz_handle_rx(info);
			cyz_handle_tx(info);
		}
		/* poll every 'cyz_polling_cycle' period */
		expires = jiffies + cyz_polling_cycle;
	}
	mod_timer(&cyz_timerlist, expires);
}