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
struct bcm_qspi {int bspi_maj_rev; } ;

/* Variables and functions */

__attribute__((used)) static inline bool bcm_qspi_bspi_ver_three(struct bcm_qspi *qspi)
{
	if (qspi->bspi_maj_rev < 4)
		return true;
	return false;
}