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
struct arizona {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_IRQ_SPK_OVERHEAT ; 
 int /*<<< orphan*/  ARIZONA_IRQ_SPK_OVERHEAT_WARN ; 
 int /*<<< orphan*/  arizona_free_irq (struct arizona*,int /*<<< orphan*/ ,struct arizona*) ; 

int arizona_free_spk_irqs(struct arizona *arizona)
{
	arizona_free_irq(arizona, ARIZONA_IRQ_SPK_OVERHEAT_WARN, arizona);
	arizona_free_irq(arizona, ARIZONA_IRQ_SPK_OVERHEAT, arizona);

	return 0;
}