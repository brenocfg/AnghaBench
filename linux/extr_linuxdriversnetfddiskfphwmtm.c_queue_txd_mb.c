#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* txd_tx_tail; TYPE_3__* txd_tx_pipe; int /*<<< orphan*/  queued_txd_mb; } ;
struct TYPE_6__ {TYPE_2__ hwm; } ;
struct s_smc {TYPE_1__ os; } ;
struct TYPE_8__ {struct TYPE_8__* sm_next; } ;
typedef  TYPE_3__ SMbuf ;

/* Variables and functions */
 int /*<<< orphan*/  DB_GEN (int,char*,TYPE_3__*) ; 

__attribute__((used)) static void queue_txd_mb(struct s_smc *smc, SMbuf *mb)
{
	DB_GEN(4, "_rx: queue_txd_mb = %p", mb);
	smc->os.hwm.queued_txd_mb++ ;
	mb->sm_next = (SMbuf *)NULL ;
	if (smc->os.hwm.txd_tx_pipe == NULL) {
		smc->os.hwm.txd_tx_pipe = mb ;
	}
	else {
		smc->os.hwm.txd_tx_tail->sm_next = mb ;
	}
	smc->os.hwm.txd_tx_tail = mb ;
}