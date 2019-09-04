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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int AT91_RSTC_KEY ; 
 int AT91_RSTC_PROCRST ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  at91_rstc_base ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int samx7_restart(struct notifier_block *this, unsigned long mode,
			 void *cmd)
{
	writel(cpu_to_le32(AT91_RSTC_KEY | AT91_RSTC_PROCRST),
	       at91_rstc_base);

	return NOTIFY_DONE;
}