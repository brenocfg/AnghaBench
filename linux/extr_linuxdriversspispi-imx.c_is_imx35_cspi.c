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
struct spi_imx_data {TYPE_1__* devtype_data; } ;
struct TYPE_2__ {scalar_t__ devtype; } ;

/* Variables and functions */
 scalar_t__ IMX35_CSPI ; 

__attribute__((used)) static inline int is_imx35_cspi(struct spi_imx_data *d)
{
	return d->devtype_data->devtype == IMX35_CSPI;
}