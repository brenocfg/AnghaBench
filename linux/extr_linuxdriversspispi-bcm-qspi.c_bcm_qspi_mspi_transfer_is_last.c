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
struct qspi_trans {int /*<<< orphan*/  trans; scalar_t__ mspi_last_trans; } ;
struct bcm_qspi {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 scalar_t__ spi_transfer_is_last (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bcm_qspi_mspi_transfer_is_last(struct bcm_qspi *qspi,
					   struct qspi_trans *qt)
{
	if (qt->mspi_last_trans &&
	    spi_transfer_is_last(qspi->master, qt->trans))
		return true;
	else
		return false;
}