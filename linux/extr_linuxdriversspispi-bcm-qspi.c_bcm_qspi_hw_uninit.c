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
struct bcm_qspi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSPI ; 
 int /*<<< orphan*/  MSPI_SPCR2 ; 
 int /*<<< orphan*/  MSPI_WRITE_LOCK ; 
 int /*<<< orphan*/  bcm_qspi_write (struct bcm_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ has_bspi (struct bcm_qspi*) ; 

__attribute__((used)) static void bcm_qspi_hw_uninit(struct bcm_qspi *qspi)
{
	bcm_qspi_write(qspi, MSPI, MSPI_SPCR2, 0);
	if (has_bspi(qspi))
		bcm_qspi_write(qspi, MSPI, MSPI_WRITE_LOCK, 0);

}