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
typedef  int /*<<< orphan*/  u_long ;
struct ahd_softc {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int ahd_intr (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_lock (struct ahd_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahd_unlock (struct ahd_softc*,int /*<<< orphan*/ *) ; 

irqreturn_t
ahd_linux_isr(int irq, void *dev_id)
{
	struct	ahd_softc *ahd;
	u_long	flags;
	int	ours;

	ahd = (struct ahd_softc *) dev_id;
	ahd_lock(ahd, &flags); 
	ours = ahd_intr(ahd);
	ahd_unlock(ahd, &flags);
	return IRQ_RETVAL(ours);
}