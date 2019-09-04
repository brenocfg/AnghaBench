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
 int /*<<< orphan*/  BSPI ; 
 int /*<<< orphan*/  BSPI_RAF_CTRL ; 
 int /*<<< orphan*/  BSPI_RAF_CTRL_START_MASK ; 
 int /*<<< orphan*/  bcm_qspi_bspi_busy_poll (struct bcm_qspi*) ; 
 int /*<<< orphan*/  bcm_qspi_write (struct bcm_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bcm_qspi_bspi_lr_start(struct bcm_qspi *qspi)
{
	bcm_qspi_bspi_busy_poll(qspi);
	bcm_qspi_write(qspi, BSPI, BSPI_RAF_CTRL,
		       BSPI_RAF_CTRL_START_MASK);
}