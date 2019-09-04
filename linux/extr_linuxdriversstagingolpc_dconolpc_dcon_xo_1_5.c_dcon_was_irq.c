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

/* Variables and functions */
 int BIT_GPIO12 ; 
 int /*<<< orphan*/  VX855_GPI_STATUS_CHG ; 
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dcon_was_irq(void)
{
	u8 tmp;

	/* irq status will appear in PMIO_Rx50[6] on gpio12 */
	tmp = inb(VX855_GPI_STATUS_CHG);

	return !!(tmp & BIT_GPIO12);
}