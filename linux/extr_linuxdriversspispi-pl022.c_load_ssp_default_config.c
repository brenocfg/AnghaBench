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
struct pl022 {int /*<<< orphan*/  virtbase; TYPE_1__* vendor; } ;
struct TYPE_2__ {scalar_t__ extended_cr; scalar_t__ pl023; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_ALL_INTERRUPTS ; 
 int /*<<< orphan*/  DEFAULT_SSP_REG_CPSR ; 
 int /*<<< orphan*/  DEFAULT_SSP_REG_CR0 ; 
 int /*<<< orphan*/  DEFAULT_SSP_REG_CR0_ST ; 
 int /*<<< orphan*/  DEFAULT_SSP_REG_CR0_ST_PL023 ; 
 int /*<<< orphan*/  DEFAULT_SSP_REG_CR1 ; 
 int /*<<< orphan*/  DEFAULT_SSP_REG_CR1_ST ; 
 int /*<<< orphan*/  DEFAULT_SSP_REG_CR1_ST_PL023 ; 
 int /*<<< orphan*/  DEFAULT_SSP_REG_DMACR ; 
 int /*<<< orphan*/  DISABLE_ALL_INTERRUPTS ; 
 int /*<<< orphan*/  SSP_CPSR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSP_CR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSP_CR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSP_DMACR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSP_ICR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSP_IMSC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void load_ssp_default_config(struct pl022 *pl022)
{
	if (pl022->vendor->pl023) {
		writel(DEFAULT_SSP_REG_CR0_ST_PL023, SSP_CR0(pl022->virtbase));
		writew(DEFAULT_SSP_REG_CR1_ST_PL023, SSP_CR1(pl022->virtbase));
	} else if (pl022->vendor->extended_cr) {
		writel(DEFAULT_SSP_REG_CR0_ST, SSP_CR0(pl022->virtbase));
		writew(DEFAULT_SSP_REG_CR1_ST, SSP_CR1(pl022->virtbase));
	} else {
		writew(DEFAULT_SSP_REG_CR0, SSP_CR0(pl022->virtbase));
		writew(DEFAULT_SSP_REG_CR1, SSP_CR1(pl022->virtbase));
	}
	writew(DEFAULT_SSP_REG_DMACR, SSP_DMACR(pl022->virtbase));
	writew(DEFAULT_SSP_REG_CPSR, SSP_CPSR(pl022->virtbase));
	writew(DISABLE_ALL_INTERRUPTS, SSP_IMSC(pl022->virtbase));
	writew(CLEAR_ALL_INTERRUPTS, SSP_ICR(pl022->virtbase));
}