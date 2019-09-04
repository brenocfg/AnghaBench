#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_4__ {void* ecc_size; } ;
struct ramoops_platform_data {int dump_oops; void* flags; TYPE_1__ ecc_info; void* pmsg_size; void* ftrace_size; void* console_size; void* record_size; int /*<<< orphan*/  mem_type; int /*<<< orphan*/  mem_address; int /*<<< orphan*/  mem_size; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ramoops_parse_dt_size (struct platform_device*,char*,void**) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int ramoops_parse_dt(struct platform_device *pdev,
			    struct ramoops_platform_data *pdata)
{
	struct device_node *of_node = pdev->dev.of_node;
	struct resource *res;
	u32 value;
	int ret;

	dev_dbg(&pdev->dev, "using Device Tree\n");

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev,
			"failed to locate DT /reserved-memory resource\n");
		return -EINVAL;
	}

	pdata->mem_size = resource_size(res);
	pdata->mem_address = res->start;
	pdata->mem_type = of_property_read_bool(of_node, "unbuffered");
	pdata->dump_oops = !of_property_read_bool(of_node, "no-dump-oops");

#define parse_size(name, field) {					\
		ret = ramoops_parse_dt_size(pdev, name, &value);	\
		if (ret < 0)						\
			return ret;					\
		field = value;						\
	}

	parse_size("record-size", pdata->record_size);
	parse_size("console-size", pdata->console_size);
	parse_size("ftrace-size", pdata->ftrace_size);
	parse_size("pmsg-size", pdata->pmsg_size);
	parse_size("ecc-size", pdata->ecc_info.ecc_size);
	parse_size("flags", pdata->flags);

#undef parse_size

	return 0;
}