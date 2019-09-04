#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct qoriq_ptp_registers {TYPE_3__* ctrl_regs; TYPE_2__* alarm_regs; TYPE_1__* etts_regs; } ;
struct qoriq_ptp {int alarm_value; int alarm_interval; int /*<<< orphan*/  clock; int /*<<< orphan*/  lock; struct qoriq_ptp_registers regs; } ;
struct ptp_clock_event {int index; int timestamp; void* type; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  tmr_tevent; int /*<<< orphan*/  tmr_temask; } ;
struct TYPE_5__ {int /*<<< orphan*/  tmr_alarm2_h; int /*<<< orphan*/  tmr_alarm2_l; } ;
struct TYPE_4__ {int /*<<< orphan*/  tmr_etts2_l; int /*<<< orphan*/  tmr_etts2_h; int /*<<< orphan*/  tmr_etts1_l; int /*<<< orphan*/  tmr_etts1_h; } ;

/* Variables and functions */
 int ALM2 ; 
 int ALM2EN ; 
 int ETS1 ; 
 int ETS2 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PP1 ; 
 void* PTP_CLOCK_ALARM ; 
 void* PTP_CLOCK_EXTTS ; 
 void* PTP_CLOCK_PPS ; 
 int /*<<< orphan*/  ptp_clock_event (int /*<<< orphan*/ ,struct ptp_clock_event*) ; 
 int qoriq_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qoriq_write (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t isr(int irq, void *priv)
{
	struct qoriq_ptp *qoriq_ptp = priv;
	struct qoriq_ptp_registers *regs = &qoriq_ptp->regs;
	struct ptp_clock_event event;
	u64 ns;
	u32 ack = 0, lo, hi, mask, val;

	val = qoriq_read(&regs->ctrl_regs->tmr_tevent);

	if (val & ETS1) {
		ack |= ETS1;
		hi = qoriq_read(&regs->etts_regs->tmr_etts1_h);
		lo = qoriq_read(&regs->etts_regs->tmr_etts1_l);
		event.type = PTP_CLOCK_EXTTS;
		event.index = 0;
		event.timestamp = ((u64) hi) << 32;
		event.timestamp |= lo;
		ptp_clock_event(qoriq_ptp->clock, &event);
	}

	if (val & ETS2) {
		ack |= ETS2;
		hi = qoriq_read(&regs->etts_regs->tmr_etts2_h);
		lo = qoriq_read(&regs->etts_regs->tmr_etts2_l);
		event.type = PTP_CLOCK_EXTTS;
		event.index = 1;
		event.timestamp = ((u64) hi) << 32;
		event.timestamp |= lo;
		ptp_clock_event(qoriq_ptp->clock, &event);
	}

	if (val & ALM2) {
		ack |= ALM2;
		if (qoriq_ptp->alarm_value) {
			event.type = PTP_CLOCK_ALARM;
			event.index = 0;
			event.timestamp = qoriq_ptp->alarm_value;
			ptp_clock_event(qoriq_ptp->clock, &event);
		}
		if (qoriq_ptp->alarm_interval) {
			ns = qoriq_ptp->alarm_value + qoriq_ptp->alarm_interval;
			hi = ns >> 32;
			lo = ns & 0xffffffff;
			spin_lock(&qoriq_ptp->lock);
			qoriq_write(&regs->alarm_regs->tmr_alarm2_l, lo);
			qoriq_write(&regs->alarm_regs->tmr_alarm2_h, hi);
			spin_unlock(&qoriq_ptp->lock);
			qoriq_ptp->alarm_value = ns;
		} else {
			qoriq_write(&regs->ctrl_regs->tmr_tevent, ALM2);
			spin_lock(&qoriq_ptp->lock);
			mask = qoriq_read(&regs->ctrl_regs->tmr_temask);
			mask &= ~ALM2EN;
			qoriq_write(&regs->ctrl_regs->tmr_temask, mask);
			spin_unlock(&qoriq_ptp->lock);
			qoriq_ptp->alarm_value = 0;
			qoriq_ptp->alarm_interval = 0;
		}
	}

	if (val & PP1) {
		ack |= PP1;
		event.type = PTP_CLOCK_PPS;
		ptp_clock_event(qoriq_ptp->clock, &event);
	}

	if (ack) {
		qoriq_write(&regs->ctrl_regs->tmr_tevent, ack);
		return IRQ_HANDLED;
	} else
		return IRQ_NONE;
}