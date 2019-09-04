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
struct TYPE_3__ {int /*<<< orphan*/  sync; int /*<<< orphan*/  cmd; TYPE_2__* data; } ;
struct ucsi_acpi {int /*<<< orphan*/  ucsi; TYPE_1__ ppm; int /*<<< orphan*/ * dev; int /*<<< orphan*/  guid; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_4__ {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UCSI_DSM_UUID ; 
 int /*<<< orphan*/  acpi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucsi_acpi*) ; 
 int /*<<< orphan*/  acpi_release_memory (int /*<<< orphan*/ ,struct resource*,int) ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ucsi_acpi* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int guid_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ucsi_acpi*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  ucsi_acpi_cmd ; 
 int /*<<< orphan*/  ucsi_acpi_notify ; 
 int /*<<< orphan*/  ucsi_acpi_sync ; 
 int /*<<< orphan*/  ucsi_register_ppm (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int ucsi_acpi_probe(struct platform_device *pdev)
{
	struct ucsi_acpi *ua;
	struct resource *res;
	acpi_status status;
	int ret;

	ua = devm_kzalloc(&pdev->dev, sizeof(*ua), GFP_KERNEL);
	if (!ua)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "missing memory resource\n");
		return -ENODEV;
	}

	/* This will make sure we can use ioremap_nocache() */
	status = acpi_release_memory(ACPI_HANDLE(&pdev->dev), res, 1);
	if (ACPI_FAILURE(status))
		return -ENOMEM;

	/*
	 * NOTE: The memory region for the data structures is used also in an
	 * operation region, which means ACPI has already reserved it. Therefore
	 * it can not be requested here, and we can not use
	 * devm_ioremap_resource().
	 */
	ua->ppm.data = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	if (!ua->ppm.data)
		return -ENOMEM;

	if (!ua->ppm.data->version)
		return -ENODEV;

	ret = guid_parse(UCSI_DSM_UUID, &ua->guid);
	if (ret)
		return ret;

	ua->ppm.cmd = ucsi_acpi_cmd;
	ua->ppm.sync = ucsi_acpi_sync;
	ua->dev = &pdev->dev;

	status = acpi_install_notify_handler(ACPI_HANDLE(&pdev->dev),
					     ACPI_DEVICE_NOTIFY,
					     ucsi_acpi_notify, ua);
	if (ACPI_FAILURE(status)) {
		dev_err(&pdev->dev, "failed to install notify handler\n");
		return -ENODEV;
	}

	ua->ucsi = ucsi_register_ppm(&pdev->dev, &ua->ppm);
	if (IS_ERR(ua->ucsi)) {
		acpi_remove_notify_handler(ACPI_HANDLE(&pdev->dev),
					   ACPI_DEVICE_NOTIFY,
					   ucsi_acpi_notify);
		return PTR_ERR(ua->ucsi);
	}

	platform_set_drvdata(pdev, ua);

	return 0;
}