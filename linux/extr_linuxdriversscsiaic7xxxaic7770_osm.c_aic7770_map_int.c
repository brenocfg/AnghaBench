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
typedef  int /*<<< orphan*/  u_int ;
struct ahc_softc {int flags; TYPE_1__* platform_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int AHC_EDGE_INTERRUPT ; 
 int IRQF_SHARED ; 
 int /*<<< orphan*/  ahc_linux_isr ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct ahc_softc*) ; 

int
aic7770_map_int(struct ahc_softc *ahc, u_int irq)
{
	int error;
	int shared;

	shared = 0;
	if ((ahc->flags & AHC_EDGE_INTERRUPT) == 0)
		shared = IRQF_SHARED;

	error = request_irq(irq, ahc_linux_isr, shared, "aic7xxx", ahc);
	if (error == 0)
		ahc->platform_data->irq = irq;
	
	return (-error);
}