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
typedef  int /*<<< orphan*/  u_long ;
struct pci_dev {int dummy; } ;
struct ahd_softc {TYPE_1__* platform_data; } ;
struct TYPE_2__ {scalar_t__ host; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ahd_free (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_intr_enable (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_lock (struct ahd_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahd_unlock (struct ahd_softc*,int /*<<< orphan*/ *) ; 
 struct ahd_softc* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_remove_host (scalar_t__) ; 

__attribute__((used)) static void
ahd_linux_pci_dev_remove(struct pci_dev *pdev)
{
	struct ahd_softc *ahd = pci_get_drvdata(pdev);
	u_long s;

	if (ahd->platform_data && ahd->platform_data->host)
			scsi_remove_host(ahd->platform_data->host);

	ahd_lock(ahd, &s);
	ahd_intr_enable(ahd, FALSE);
	ahd_unlock(ahd, &s);
	ahd_free(ahd);
}