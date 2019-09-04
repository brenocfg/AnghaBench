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
struct scc_channel {int* wreg; int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRSRC ; 
 int /*<<< orphan*/  OutReg (int /*<<< orphan*/ ,size_t,int) ; 
 size_t R14 ; 
 int SNRZI ; 
 int SSBR ; 
 int /*<<< orphan*/  wr (struct scc_channel*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void init_brg(struct scc_channel *scc)
{
	wr(scc, R14, BRSRC);				/* BRG source = PCLK */
	OutReg(scc->ctrl, R14, SSBR|scc->wreg[R14]);	/* DPLL source = BRG */
	OutReg(scc->ctrl, R14, SNRZI|scc->wreg[R14]);	/* DPLL NRZI mode */
}