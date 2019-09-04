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
struct spi_slave_time_priv {int /*<<< orphan*/  finished; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 struct spi_slave_time_priv* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  spi_slave_abort (struct spi_device*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spi_slave_time_remove(struct spi_device *spi)
{
	struct spi_slave_time_priv *priv = spi_get_drvdata(spi);

	spi_slave_abort(spi);
	wait_for_completion(&priv->finished);
	return 0;
}