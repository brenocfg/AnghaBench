#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spi_message {TYPE_1__* spi; } ;
struct spi_master {int dummy; } ;
struct lantiq_ssc_spi {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_enter_active_mode (struct lantiq_ssc_spi*) ; 
 int /*<<< orphan*/  hw_enter_config_mode (struct lantiq_ssc_spi*) ; 
 int /*<<< orphan*/  hw_setup_clock_mode (struct lantiq_ssc_spi*,int /*<<< orphan*/ ) ; 
 struct lantiq_ssc_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int lantiq_ssc_prepare_message(struct spi_master *master,
				      struct spi_message *message)
{
	struct lantiq_ssc_spi *spi = spi_master_get_devdata(master);

	hw_enter_config_mode(spi);
	hw_setup_clock_mode(spi, message->spi->mode);
	hw_enter_active_mode(spi);

	return 0;
}