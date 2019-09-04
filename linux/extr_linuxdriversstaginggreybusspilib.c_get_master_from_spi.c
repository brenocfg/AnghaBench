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
struct spi_master {int dummy; } ;
struct gb_spilib {int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 struct spi_master* gb_connection_get_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct spi_master *get_master_from_spi(struct gb_spilib *spi)
{
	return gb_connection_get_data(spi->connection);
}