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
struct hpc3_ethregs {int reset; } ;

/* Variables and functions */
 int HPC3_ERST_CLRIRQ ; 
 int HPC3_ERST_CRESET ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void hpc3_eth_reset(struct hpc3_ethregs *hregs)
{
	hregs->reset = HPC3_ERST_CRESET | HPC3_ERST_CLRIRQ;
	udelay(20);
	hregs->reset = 0;
}