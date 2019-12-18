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
struct atiixp_modem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  ISR ; 
 int /*<<< orphan*/  atiixp_read (struct atiixp_modem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_write (struct atiixp_modem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_atiixp_chip_stop(struct atiixp_modem *chip)
{
	/* clear interrupt source */
	atiixp_write(chip, ISR, atiixp_read(chip, ISR));
	/* disable irqs */
	atiixp_write(chip, IER, 0);
	return 0;
}