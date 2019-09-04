#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  errnotify_isr_cnt; int /*<<< orphan*/  last_isr_time; } ;
struct TYPE_4__ {TYPE_1__ misc; } ;
struct snic {int /*<<< orphan*/ * intr; TYPE_2__ s_stats; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 size_t SNIC_MSIX_ERR_NOTIFY ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  snic_handle_link_event (struct snic*) ; 
 int /*<<< orphan*/  snic_log_q_error (struct snic*) ; 
 int /*<<< orphan*/  svnic_intr_return_all_credits (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
snic_isr_msix_err_notify(int irq, void *data)
{
	struct snic *snic = data;

	snic->s_stats.misc.last_isr_time = jiffies;
	atomic64_inc(&snic->s_stats.misc.errnotify_isr_cnt);

	svnic_intr_return_all_credits(&snic->intr[SNIC_MSIX_ERR_NOTIFY]);
	snic_log_q_error(snic);

	/*Handling link events */
	snic_handle_link_event(snic);

	return IRQ_HANDLED;
}