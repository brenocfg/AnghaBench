#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  invert_polarity; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OMAP_DSS_VENC_TYPE_COMPOSITE ; 
 int /*<<< orphan*/  OMAP_DSS_VENC_TYPE_SVIDEO ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 struct device_node* omapdss_of_get_first_endpoint (struct device_node*) ; 
 TYPE_1__ venc ; 

__attribute__((used)) static int venc_probe_of(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct device_node *ep;
	u32 channels;
	int r;

	ep = omapdss_of_get_first_endpoint(node);
	if (!ep)
		return 0;

	venc.invert_polarity = of_property_read_bool(ep, "ti,invert-polarity");

	r = of_property_read_u32(ep, "ti,channels", &channels);
	if (r) {
		dev_err(&pdev->dev,
			"failed to read property 'ti,channels': %d\n", r);
		goto err;
	}

	switch (channels) {
	case 1:
		venc.type = OMAP_DSS_VENC_TYPE_COMPOSITE;
		break;
	case 2:
		venc.type = OMAP_DSS_VENC_TYPE_SVIDEO;
		break;
	default:
		dev_err(&pdev->dev, "bad channel propert '%d'\n", channels);
		r = -EINVAL;
		goto err;
	}

	of_node_put(ep);

	return 0;
err:
	of_node_put(ep);

	return 0;
}