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
struct spi_slave {int dummy; } ;
struct ar71xx_spi_slave {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ar71xx_spi_slave*) ; 
 struct ar71xx_spi_slave* to_ar71xx_spi (struct spi_slave*) ; 

void spi_free_slave(struct spi_slave *slave)
{
	struct ar71xx_spi_slave *ss = to_ar71xx_spi(slave);

	free(ss);
}