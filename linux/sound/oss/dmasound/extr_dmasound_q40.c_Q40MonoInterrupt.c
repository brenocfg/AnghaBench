#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DAC_LEFT ; 
 int /*<<< orphan*/ * DAC_RIGHT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  Q40Interrupt () ; 
 int /*<<< orphan*/  SAMPLE_CLEAR_REG ; 
 TYPE_1__ dmasound ; 
 int /*<<< orphan*/  master_outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * q40_pp ; 
 scalar_t__ q40_sc ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t Q40MonoInterrupt(int irq, void *dummy)
{
	spin_lock(&dmasound.lock);
        if (q40_sc>0){
            *DAC_LEFT=*q40_pp;
	    *DAC_RIGHT=*q40_pp++;
	    q40_sc --;
	    master_outb(1,SAMPLE_CLEAR_REG);
	}else Q40Interrupt();
	spin_unlock(&dmasound.lock);
	return IRQ_HANDLED;
}