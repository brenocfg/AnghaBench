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
struct s_smt_rx_queue {void* rx_bmu_dsc; void* rx_bmu_ctl; } ;
struct TYPE_3__ {struct s_smt_rx_queue* rx_q; struct s_smt_rx_queue** rx; } ;
struct TYPE_4__ {TYPE_1__ fp; } ;
struct s_smc {TYPE_2__ hw; } ;
typedef  void* HW_PTR ;

/* Variables and functions */
 scalar_t__ ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B0_R1_CSR ; 
 int /*<<< orphan*/  B0_R2_CSR ; 
 int /*<<< orphan*/  B4_R1_DA ; 
 int /*<<< orphan*/  B4_R2_DA ; 
 size_t QUEUE_R1 ; 
 size_t QUEUE_R2 ; 

__attribute__((used)) static void init_rx(struct s_smc *smc)
{
	struct s_smt_rx_queue	*queue ;

	/*
	 * init all tx data structures for receive queue 1
	 */
	smc->hw.fp.rx[QUEUE_R1] = queue = &smc->hw.fp.rx_q[QUEUE_R1] ;
	queue->rx_bmu_ctl = (HW_PTR) ADDR(B0_R1_CSR) ;
	queue->rx_bmu_dsc = (HW_PTR) ADDR(B4_R1_DA) ;

	/*
	 * init all tx data structures for receive queue 2
	 */
	smc->hw.fp.rx[QUEUE_R2] = queue = &smc->hw.fp.rx_q[QUEUE_R2] ;
	queue->rx_bmu_ctl = (HW_PTR) ADDR(B0_R2_CSR) ;
	queue->rx_bmu_dsc = (HW_PTR) ADDR(B4_R2_DA) ;
}