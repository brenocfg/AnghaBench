#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int irq; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ SB16 ;

/* Variables and functions */
 int /*<<< orphan*/  MIXER_INTERRUPT_SETUP_REGISTER ; 
 int read_mixer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned char get_irq(SB16* sb16)
{
	unsigned char irq;
	irq=(read_mixer(sb16->base,MIXER_INTERRUPT_SETUP_REGISTER)&0x0f);

	if(irq==1) sb16->irq=2;
	if(irq==2) sb16->irq=5;
	if(irq==4) sb16->irq=7;
	if(irq==8) sb16->irq=10;
	return 0;
}