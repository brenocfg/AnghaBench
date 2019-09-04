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
typedef  int u32 ;
struct iproc_msi {scalar_t__ eq_cpu; } ;

/* Variables and functions */
 int hwirq_to_canonical_hwirq (struct iproc_msi*,int) ; 
 int iproc_msi_eq_offset (struct iproc_msi*,int) ; 
 int readl (int*) ; 

__attribute__((used)) static inline u32 decode_msi_hwirq(struct iproc_msi *msi, u32 eq, u32 head)
{
	u32 *msg, hwirq;
	unsigned int offs;

	offs = iproc_msi_eq_offset(msi, eq) + head * sizeof(u32);
	msg = (u32 *)(msi->eq_cpu + offs);
	hwirq = readl(msg);
	hwirq = (hwirq >> 5) + (hwirq & 0x1f);

	/*
	 * Since we have multiple hwirq mapped to a single MSI vector,
	 * now we need to derive the hwirq at CPU0.  It can then be used to
	 * mapped back to virq.
	 */
	return hwirq_to_canonical_hwirq(msi, hwirq);
}