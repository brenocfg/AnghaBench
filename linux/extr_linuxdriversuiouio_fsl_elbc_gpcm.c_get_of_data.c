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
typedef  int /*<<< orphan*/  u32 ;
struct resource {int dummy; } ;
struct fsl_elbc_gpcm {char* name; int /*<<< orphan*/  dev; int /*<<< orphan*/  bank; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int check_of_data (struct fsl_elbc_gpcm*,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 scalar_t__ of_property_read_string (struct device_node*,char*,char const**) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_periph (struct fsl_elbc_gpcm*,char const*) ; 

__attribute__((used)) static int get_of_data(struct fsl_elbc_gpcm *priv, struct device_node *node,
		       struct resource *res, u32 *reg_br,
		       u32 *reg_or, unsigned int *irq, char **name)
{
	const char *dt_name;
	const char *type;
	int ret;

	/* get the memory resource */
	ret = of_address_to_resource(node, 0, res);
	if (ret) {
		dev_err(priv->dev, "failed to get resource\n");
		return ret;
	}

	/* get the bank number */
	ret = of_property_read_u32(node, "reg", &priv->bank);
	if (ret) {
		dev_err(priv->dev, "failed to get bank number\n");
		return ret;
	}

	/* get BR value to set */
	ret = of_property_read_u32(node, "elbc-gpcm-br", reg_br);
	if (ret) {
		dev_err(priv->dev, "missing elbc-gpcm-br value\n");
		return ret;
	}

	/* get OR value to set */
	ret = of_property_read_u32(node, "elbc-gpcm-or", reg_or);
	if (ret) {
		dev_err(priv->dev, "missing elbc-gpcm-or value\n");
		return ret;
	}

	/* get optional peripheral type */
	priv->name = "generic";
	if (of_property_read_string(node, "device_type", &type) == 0)
		setup_periph(priv, type);

	/* get optional irq value */
	*irq = irq_of_parse_and_map(node, 0);

	/* sanity check device tree data */
	ret = check_of_data(priv, res, *reg_br, *reg_or);
	if (ret)
		return ret;

	/* get optional uio name */
	if (of_property_read_string(node, "uio_name", &dt_name) != 0)
		dt_name = "eLBC_GPCM";
	*name = kstrdup(dt_name, GFP_KERNEL);
	if (!*name)
		return -ENOMEM;

	return 0;
}