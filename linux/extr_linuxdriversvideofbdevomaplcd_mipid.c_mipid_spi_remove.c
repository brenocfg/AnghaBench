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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct mipid_device {int /*<<< orphan*/  panel; } ;

/* Variables and functions */
 struct mipid_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mipid_device*) ; 
 int /*<<< orphan*/  mipid_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mipid_spi_remove(struct spi_device *spi)
{
	struct mipid_device *md = dev_get_drvdata(&spi->dev);

	mipid_disable(&md->panel);
	kfree(md);

	return 0;
}