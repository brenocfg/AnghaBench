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
struct spi_message {int dummy; } ;
struct spi_master {int dummy; } ;
struct rockchip_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_enable_chip (struct rockchip_spi*,int /*<<< orphan*/ ) ; 
 struct rockchip_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int rockchip_spi_unprepare_message(struct spi_master *master,
					  struct spi_message *msg)
{
	struct rockchip_spi *rs = spi_master_get_devdata(master);

	spi_enable_chip(rs, 0);

	return 0;
}