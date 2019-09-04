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
struct dw_spi {scalar_t__ rx_end; scalar_t__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dw_reader (struct dw_spi*) ; 
 int /*<<< orphan*/  dw_writer (struct dw_spi*) ; 

__attribute__((used)) static int poll_transfer(struct dw_spi *dws)
{
	do {
		dw_writer(dws);
		dw_reader(dws);
		cpu_relax();
	} while (dws->rx_end > dws->rx);

	return 0;
}