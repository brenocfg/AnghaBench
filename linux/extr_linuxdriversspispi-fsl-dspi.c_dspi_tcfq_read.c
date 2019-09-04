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
struct fsl_dspi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dspi_push_rx (struct fsl_dspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fifo_read (struct fsl_dspi*) ; 

__attribute__((used)) static void dspi_tcfq_read(struct fsl_dspi *dspi)
{
	dspi_push_rx(dspi, fifo_read(dspi));
}