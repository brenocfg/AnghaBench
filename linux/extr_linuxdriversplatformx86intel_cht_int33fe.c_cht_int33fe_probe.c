#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct i2c_board_info {char* dev_name; int irq; int /*<<< orphan*/  type; int /*<<< orphan*/  properties; } ;
struct cht_int33fe_data {TYPE_1__* connections; void* max17047; void* fusb302; void* pi3usb30532; } ;
typedef  int /*<<< orphan*/  board_info ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_3__ {char** endpoint; char* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (struct device*) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 unsigned long long EXPECTED_PTYPE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 int acpi_dev_gpio_irq_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_dev_present (char*,char*,int) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 struct i2c_client* cht_int33fe_find_max17047 () ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int device_add_properties (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_connections_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_connections_remove (TYPE_1__*) ; 
 int device_reprobe (struct device*) ; 
 struct cht_int33fe_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fusb302_props ; 
 void* i2c_acpi_new_device (struct device*,int,struct i2c_board_info*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct cht_int33fe_data*) ; 
 int /*<<< orphan*/  i2c_unregister_device (void*) ; 
 int /*<<< orphan*/  max17047_props ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 struct regulator* regulator_get_optional (struct device*,char*) ; 
 int /*<<< orphan*/  regulator_put (struct regulator*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cht_int33fe_probe(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	struct i2c_board_info board_info;
	struct cht_int33fe_data *data;
	struct i2c_client *max17047;
	struct regulator *regulator;
	unsigned long long ptyp;
	acpi_status status;
	int fusb302_irq;
	int ret;

	status = acpi_evaluate_integer(ACPI_HANDLE(dev), "PTYP", NULL, &ptyp);
	if (ACPI_FAILURE(status)) {
		dev_err(dev, "Error getting PTYPE\n");
		return -ENODEV;
	}

	/*
	 * The same ACPI HID is used for different configurations check PTYP
	 * to ensure that we are dealing with the expected config.
	 */
	if (ptyp != EXPECTED_PTYPE)
		return -ENODEV;

	/* Check presence of INT34D3 (hardware-rev 3) expected for ptype == 4 */
	if (!acpi_dev_present("INT34D3", "1", 3)) {
		dev_err(dev, "Error PTYPE == %d, but no INT34D3 device\n",
			EXPECTED_PTYPE);
		return -ENODEV;
	}

	/*
	 * We expect the WC PMIC to be paired with a TI bq24292i charger-IC.
	 * We check for the bq24292i vbus regulator here, this has 2 purposes:
	 * 1) The bq24292i allows charging with up to 12V, setting the fusb302's
	 *    max-snk voltage to 12V with another charger-IC is not good.
	 * 2) For the fusb302 driver to get the bq24292i vbus regulator, the
	 *    regulator-map, which is part of the bq24292i regulator_init_data,
	 *    must be registered before the fusb302 is instantiated, otherwise
	 *    it will end up with a dummy-regulator.
	 * Note "cht_wc_usb_typec_vbus" comes from the regulator_init_data
	 * which is defined in i2c-cht-wc.c from where the bq24292i i2c-client
	 * gets instantiated. We use regulator_get_optional here so that we
	 * don't end up getting a dummy-regulator ourselves.
	 */
	regulator = regulator_get_optional(dev, "cht_wc_usb_typec_vbus");
	if (IS_ERR(regulator)) {
		ret = PTR_ERR(regulator);
		return (ret == -ENODEV) ? -EPROBE_DEFER : ret;
	}
	regulator_put(regulator);

	/* The FUSB302 uses the irq at index 1 and is the only irq user */
	fusb302_irq = acpi_dev_gpio_irq_get(ACPI_COMPANION(dev), 1);
	if (fusb302_irq < 0) {
		if (fusb302_irq != -EPROBE_DEFER)
			dev_err(dev, "Error getting FUSB302 irq\n");
		return fusb302_irq;
	}

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	/* Work around BIOS bug, see comment on cht_int33fe_find_max17047 */
	max17047 = cht_int33fe_find_max17047();
	if (max17047) {
		/* Pre-existing i2c-client for the max17047, add device-props */
		ret = device_add_properties(&max17047->dev, max17047_props);
		if (ret)
			return ret;
		/* And re-probe to get the new device-props applied. */
		ret = device_reprobe(&max17047->dev);
		if (ret)
			dev_warn(dev, "Reprobing max17047 error: %d\n", ret);
	} else {
		memset(&board_info, 0, sizeof(board_info));
		strlcpy(board_info.type, "max17047", I2C_NAME_SIZE);
		board_info.dev_name = "max17047";
		board_info.properties = max17047_props;
		data->max17047 = i2c_acpi_new_device(dev, 1, &board_info);
		if (!data->max17047)
			return -EPROBE_DEFER; /* Wait for i2c-adapter to load */
	}

	data->connections[0].endpoint[0] = "port0";
	data->connections[0].endpoint[1] = "i2c-pi3usb30532";
	data->connections[0].id = "typec-switch";
	data->connections[1].endpoint[0] = "port0";
	data->connections[1].endpoint[1] = "i2c-pi3usb30532";
	data->connections[1].id = "typec-mux";
	data->connections[2].endpoint[0] = "port0";
	data->connections[2].endpoint[1] = "i2c-pi3usb30532";
	data->connections[2].id = "idff01m01";
	data->connections[3].endpoint[0] = "i2c-fusb302";
	data->connections[3].endpoint[1] = "intel_xhci_usb_sw-role-switch";
	data->connections[3].id = "usb-role-switch";

	device_connections_add(data->connections);

	memset(&board_info, 0, sizeof(board_info));
	strlcpy(board_info.type, "typec_fusb302", I2C_NAME_SIZE);
	board_info.dev_name = "fusb302";
	board_info.properties = fusb302_props;
	board_info.irq = fusb302_irq;

	data->fusb302 = i2c_acpi_new_device(dev, 2, &board_info);
	if (!data->fusb302)
		goto out_unregister_max17047;

	memset(&board_info, 0, sizeof(board_info));
	board_info.dev_name = "pi3usb30532";
	strlcpy(board_info.type, "pi3usb30532", I2C_NAME_SIZE);

	data->pi3usb30532 = i2c_acpi_new_device(dev, 3, &board_info);
	if (!data->pi3usb30532)
		goto out_unregister_fusb302;

	i2c_set_clientdata(client, data);

	return 0;

out_unregister_fusb302:
	i2c_unregister_device(data->fusb302);

out_unregister_max17047:
	if (data->max17047)
		i2c_unregister_device(data->max17047);

	device_connections_remove(data->connections);

	return -EPROBE_DEFER; /* Wait for the i2c-adapter to load */
}