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
struct spi_device {int dummy; } ;
struct nfcmrvl_spi_drv_data {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfcmrvl_nci_unregister_dev (int /*<<< orphan*/ ) ; 
 struct nfcmrvl_spi_drv_data* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int nfcmrvl_spi_remove(struct spi_device *spi)
{
	struct nfcmrvl_spi_drv_data *drv_data = spi_get_drvdata(spi);

	nfcmrvl_nci_unregister_dev(drv_data->priv);
	return 0;
}