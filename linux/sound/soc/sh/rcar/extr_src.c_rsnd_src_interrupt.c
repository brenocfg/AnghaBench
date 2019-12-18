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
struct rsnd_mod {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  __rsnd_src_interrupt ; 
 int /*<<< orphan*/  rsnd_mod_interrupt (struct rsnd_mod*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rsnd_src_interrupt(int irq, void *data)
{
	struct rsnd_mod *mod = data;

	rsnd_mod_interrupt(mod, __rsnd_src_interrupt);

	return IRQ_HANDLED;
}