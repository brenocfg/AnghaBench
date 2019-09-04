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
struct TYPE_4__ {int of_reset_n_cells; int /*<<< orphan*/  of_xlate; scalar_t__ of_node; int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; } ;
struct ti_sci_reset_data {TYPE_1__ rcdev; int /*<<< orphan*/  idr; TYPE_2__* dev; int /*<<< orphan*/  sci; } ;
struct TYPE_5__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct ti_sci_reset_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ti_sci_get_handle (TYPE_2__*) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ti_sci_reset_data*) ; 
 int reset_controller_register (TYPE_1__*) ; 
 int /*<<< orphan*/  ti_sci_reset_of_xlate ; 
 int /*<<< orphan*/  ti_sci_reset_ops ; 

__attribute__((used)) static int ti_sci_reset_probe(struct platform_device *pdev)
{
	struct ti_sci_reset_data *data;

	if (!pdev->dev.of_node)
		return -ENODEV;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->sci = devm_ti_sci_get_handle(&pdev->dev);
	if (IS_ERR(data->sci))
		return PTR_ERR(data->sci);

	data->rcdev.ops = &ti_sci_reset_ops;
	data->rcdev.owner = THIS_MODULE;
	data->rcdev.of_node = pdev->dev.of_node;
	data->rcdev.of_reset_n_cells = 2;
	data->rcdev.of_xlate = ti_sci_reset_of_xlate;
	data->dev = &pdev->dev;
	idr_init(&data->idr);

	platform_set_drvdata(pdev, data);

	return reset_controller_register(&data->rcdev);
}