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
typedef  int u8 ;
struct miphy28lp_phy {scalar_t__ base; } ;

/* Variables and functions */
 int COMP_DONE ; 
 int EBUSY ; 
 int HZ ; 
 scalar_t__ MIPHY_COMP_FSM_6 ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int jiffies ; 
 int readb_relaxed (scalar_t__) ; 
 scalar_t__ time_after_eq (int,unsigned long) ; 

__attribute__((used)) static inline int miphy28lp_wait_compensation(struct miphy28lp_phy *miphy_phy)
{
	unsigned long finish = jiffies + 5 * HZ;
	u8 val;

	/* Waiting for Compensation to complete */
	do {
		val = readb_relaxed(miphy_phy->base + MIPHY_COMP_FSM_6);

		if (time_after_eq(jiffies, finish))
			return -EBUSY;
		cpu_relax();
	} while (!(val & COMP_DONE));

	return 0;
}