#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct qoriq_ptp_registers {TYPE_1__* alarm_regs; } ;
struct qoriq_ptp {scalar_t__ tclk_period; struct qoriq_ptp_registers regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  tmr_alarm1_h; int /*<<< orphan*/  tmr_alarm1_l; } ;

/* Variables and functions */
 unsigned long long div_u64 (int,unsigned long) ; 
 int /*<<< orphan*/  qoriq_write (int /*<<< orphan*/ *,int) ; 
 int tmr_cnt_read (struct qoriq_ptp*) ; 

__attribute__((used)) static void set_alarm(struct qoriq_ptp *qoriq_ptp)
{
	struct qoriq_ptp_registers *regs = &qoriq_ptp->regs;
	u64 ns;
	u32 lo, hi;

	ns = tmr_cnt_read(qoriq_ptp) + 1500000000ULL;
	ns = div_u64(ns, 1000000000UL) * 1000000000ULL;
	ns -= qoriq_ptp->tclk_period;
	hi = ns >> 32;
	lo = ns & 0xffffffff;
	qoriq_write(&regs->alarm_regs->tmr_alarm1_l, lo);
	qoriq_write(&regs->alarm_regs->tmr_alarm1_h, hi);
}