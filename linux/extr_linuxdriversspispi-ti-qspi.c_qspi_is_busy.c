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
typedef  int u32 ;
struct ti_qspi {int dummy; } ;

/* Variables and functions */
 int BUSY ; 
 unsigned long QSPI_COMPLETION_TIMEOUT ; 
 int /*<<< orphan*/  QSPI_SPI_STATUS_REG ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 int ti_qspi_read (struct ti_qspi*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static inline u32 qspi_is_busy(struct ti_qspi *qspi)
{
	u32 stat;
	unsigned long timeout = jiffies + QSPI_COMPLETION_TIMEOUT;

	stat = ti_qspi_read(qspi, QSPI_SPI_STATUS_REG);
	while ((stat & BUSY) && time_after(timeout, jiffies)) {
		cpu_relax();
		stat = ti_qspi_read(qspi, QSPI_SPI_STATUS_REG);
	}

	WARN(stat & BUSY, "qspi busy\n");
	return stat & BUSY;
}