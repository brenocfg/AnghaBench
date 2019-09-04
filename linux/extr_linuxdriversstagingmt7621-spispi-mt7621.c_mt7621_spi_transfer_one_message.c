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
struct spi_message {struct spi_device* spi; } ;
struct spi_master {int dummy; } ;
struct spi_device {int chip_select; } ;

/* Variables and functions */
 int mt7621_spi_transfer_full_duplex (struct spi_master*,struct spi_message*) ; 
 int mt7621_spi_transfer_half_duplex (struct spi_master*,struct spi_message*) ; 

__attribute__((used)) static int mt7621_spi_transfer_one_message(struct spi_master *master,
					   struct spi_message *m)
{
	struct spi_device *spi = m->spi;
	int cs = spi->chip_select;

	if (cs)
		return mt7621_spi_transfer_full_duplex(master, m);
	return mt7621_spi_transfer_half_duplex(master, m);
}