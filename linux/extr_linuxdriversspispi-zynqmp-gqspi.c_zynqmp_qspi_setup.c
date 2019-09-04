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
struct spi_device {TYPE_1__* master; } ;
struct TYPE_2__ {scalar_t__ busy; } ;

/* Variables and functions */
 int EBUSY ; 

__attribute__((used)) static int zynqmp_qspi_setup(struct spi_device *qspi)
{
	if (qspi->master->busy)
		return -EBUSY;
	return 0;
}