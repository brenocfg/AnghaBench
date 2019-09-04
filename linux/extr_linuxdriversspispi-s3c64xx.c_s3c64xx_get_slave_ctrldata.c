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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct spi_device {TYPE_1__ dev; } ;
struct s3c64xx_spi_csinfo {int /*<<< orphan*/  fb_delay; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct s3c64xx_spi_csinfo* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct s3c64xx_spi_csinfo* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct s3c64xx_spi_csinfo *s3c64xx_get_slave_ctrldata(
				struct spi_device *spi)
{
	struct s3c64xx_spi_csinfo *cs;
	struct device_node *slave_np, *data_np = NULL;
	u32 fb_delay = 0;

	slave_np = spi->dev.of_node;
	if (!slave_np) {
		dev_err(&spi->dev, "device node not found\n");
		return ERR_PTR(-EINVAL);
	}

	data_np = of_get_child_by_name(slave_np, "controller-data");
	if (!data_np) {
		dev_err(&spi->dev, "child node 'controller-data' not found\n");
		return ERR_PTR(-EINVAL);
	}

	cs = kzalloc(sizeof(*cs), GFP_KERNEL);
	if (!cs) {
		of_node_put(data_np);
		return ERR_PTR(-ENOMEM);
	}

	of_property_read_u32(data_np, "samsung,spi-feedback-delay", &fb_delay);
	cs->fb_delay = fb_delay;
	of_node_put(data_np);
	return cs;
}