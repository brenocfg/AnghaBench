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
struct vsc7385_data {int dummy; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct vsc7385_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vsc7385_data*) ; 

__attribute__((used)) static int vsc7385_remove(struct spi_device *spi)
{
	struct vsc7385_data	*vsc;

	vsc = dev_get_drvdata(&spi->dev);
	dev_set_drvdata(&spi->dev, NULL);
	kfree(vsc);

	return 0;
}