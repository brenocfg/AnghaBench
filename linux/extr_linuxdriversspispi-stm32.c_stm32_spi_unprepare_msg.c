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
struct stm32_spi {int dummy; } ;
struct spi_message {int dummy; } ;
struct spi_master {int dummy; } ;

/* Variables and functions */
 struct stm32_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  stm32_spi_disable (struct stm32_spi*) ; 

__attribute__((used)) static int stm32_spi_unprepare_msg(struct spi_master *master,
				   struct spi_message *msg)
{
	struct stm32_spi *spi = spi_master_get_devdata(master);

	stm32_spi_disable(spi);

	return 0;
}