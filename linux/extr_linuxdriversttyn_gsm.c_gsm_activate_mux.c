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
struct gsm_mux {scalar_t__ encoding; int num; scalar_t__ dead; int /*<<< orphan*/  error; int /*<<< orphan*/  receive; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  control_lock; int /*<<< orphan*/  event; int /*<<< orphan*/  t2_timer; } ;
struct gsm_dlci {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int MAX_MUX ; 
 int /*<<< orphan*/  gsm0_receive ; 
 int /*<<< orphan*/  gsm1_receive ; 
 int /*<<< orphan*/  gsm_control_retransmit ; 
 struct gsm_dlci* gsm_dlci_alloc (struct gsm_mux*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsm_error ; 
 struct gsm_mux** gsm_mux ; 
 int /*<<< orphan*/  gsm_mux_lock ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gsm_activate_mux(struct gsm_mux *gsm)
{
	struct gsm_dlci *dlci;
	int i = 0;

	timer_setup(&gsm->t2_timer, gsm_control_retransmit, 0);
	init_waitqueue_head(&gsm->event);
	spin_lock_init(&gsm->control_lock);
	spin_lock_init(&gsm->tx_lock);

	if (gsm->encoding == 0)
		gsm->receive = gsm0_receive;
	else
		gsm->receive = gsm1_receive;
	gsm->error = gsm_error;

	spin_lock(&gsm_mux_lock);
	for (i = 0; i < MAX_MUX; i++) {
		if (gsm_mux[i] == NULL) {
			gsm->num = i;
			gsm_mux[i] = gsm;
			break;
		}
	}
	spin_unlock(&gsm_mux_lock);
	if (i == MAX_MUX)
		return -EBUSY;

	dlci = gsm_dlci_alloc(gsm, 0);
	if (dlci == NULL)
		return -ENOMEM;
	gsm->dead = 0;		/* Tty opens are now permissible */
	return 0;
}