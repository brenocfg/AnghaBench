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
typedef  int u8 ;
typedef  int u16 ;
struct pch_thermal_device {int bios_enabled; int crt_trip_id; int crt_temp; int hot_trip_id; int hot_temp; scalar_t__ hw_base; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ WPT_CTT ; 
 scalar_t__ WPT_PHL ; 
 scalar_t__ WPT_TSEL ; 
 int WPT_TSEL_ETS ; 
 int WPT_TSEL_PLDB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pch_wpt_add_acpi_psv_trip (struct pch_thermal_device*,int*) ; 
 int readb (scalar_t__) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int pch_wpt_init(struct pch_thermal_device *ptd, int *nr_trips)
{
	u8 tsel;
	u16 trip_temp;

	*nr_trips = 0;

	/* Check if BIOS has already enabled thermal sensor */
	if (WPT_TSEL_ETS & readb(ptd->hw_base + WPT_TSEL)) {
		ptd->bios_enabled = true;
		goto read_trips;
	}

	tsel = readb(ptd->hw_base + WPT_TSEL);
	/*
	 * When TSEL's Policy Lock-Down bit is 1, TSEL become RO.
	 * If so, thermal sensor cannot enable. Bail out.
	 */
	if (tsel & WPT_TSEL_PLDB) {
		dev_err(&ptd->pdev->dev, "Sensor can't be enabled\n");
		return -ENODEV;
	}

	writeb(tsel|WPT_TSEL_ETS, ptd->hw_base + WPT_TSEL);
	if (!(WPT_TSEL_ETS & readb(ptd->hw_base + WPT_TSEL))) {
		dev_err(&ptd->pdev->dev, "Sensor can't be enabled\n");
		return -ENODEV;
	}

read_trips:
	ptd->crt_trip_id = -1;
	trip_temp = readw(ptd->hw_base + WPT_CTT);
	trip_temp &= 0x1FF;
	if (trip_temp) {
		/* Resolution of 1/2 degree C and an offset of -50C */
		ptd->crt_temp = trip_temp * 1000 / 2 - 50000;
		ptd->crt_trip_id = 0;
		++(*nr_trips);
	}

	ptd->hot_trip_id = -1;
	trip_temp = readw(ptd->hw_base + WPT_PHL);
	trip_temp &= 0x1FF;
	if (trip_temp) {
		/* Resolution of 1/2 degree C and an offset of -50C */
		ptd->hot_temp = trip_temp * 1000 / 2 - 50000;
		ptd->hot_trip_id = *nr_trips;
		++(*nr_trips);
	}

	pch_wpt_add_acpi_psv_trip(ptd, nr_trips);

	return 0;
}