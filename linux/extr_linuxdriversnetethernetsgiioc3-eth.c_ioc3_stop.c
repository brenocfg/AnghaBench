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
struct ioc3_private {struct ioc3* regs; } ;
struct ioc3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioc3_r_eier () ; 
 int /*<<< orphan*/  ioc3_w_eier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc3_w_emcr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ioc3_stop(struct ioc3_private *ip)
{
	struct ioc3 *ioc3 = ip->regs;

	ioc3_w_emcr(0);				/* Shutup */
	ioc3_w_eier(0);				/* Disable interrupts */
	(void) ioc3_r_eier();			/* Flush */
}