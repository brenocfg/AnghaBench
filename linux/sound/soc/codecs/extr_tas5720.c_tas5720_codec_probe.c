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
struct tas5720_data {int devtype; int /*<<< orphan*/  supplies; int /*<<< orphan*/  fault_check_work; int /*<<< orphan*/  regmap; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  TAS5720 129 
 unsigned int TAS5720_DEVICE_ID ; 
 int /*<<< orphan*/  TAS5720_DEVICE_ID_REG ; 
 int /*<<< orphan*/  TAS5720_DIGITAL_CTRL2_REG ; 
 int /*<<< orphan*/  TAS5720_MUTE ; 
 int /*<<< orphan*/  TAS5720_POWER_CTRL_REG ; 
 int /*<<< orphan*/  TAS5720_SDZ ; 
#define  TAS5722 128 
 unsigned int TAS5722_DEVICE_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tas5720_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tas5720_fault_check_work ; 

__attribute__((used)) static int tas5720_codec_probe(struct snd_soc_component *component)
{
	struct tas5720_data *tas5720 = snd_soc_component_get_drvdata(component);
	unsigned int device_id, expected_device_id;
	int ret;

	tas5720->component = component;

	ret = regulator_bulk_enable(ARRAY_SIZE(tas5720->supplies),
				    tas5720->supplies);
	if (ret != 0) {
		dev_err(component->dev, "failed to enable supplies: %d\n", ret);
		return ret;
	}

	/*
	 * Take a liberal approach to checking the device ID to allow the
	 * driver to be used even if the device ID does not match, however
	 * issue a warning if there is a mismatch.
	 */
	ret = regmap_read(tas5720->regmap, TAS5720_DEVICE_ID_REG, &device_id);
	if (ret < 0) {
		dev_err(component->dev, "failed to read device ID register: %d\n",
			ret);
		goto probe_fail;
	}

	switch (tas5720->devtype) {
	case TAS5720:
		expected_device_id = TAS5720_DEVICE_ID;
		break;
	case TAS5722:
		expected_device_id = TAS5722_DEVICE_ID;
		break;
	default:
		dev_err(component->dev, "unexpected private driver data\n");
		return -EINVAL;
	}

	if (device_id != expected_device_id)
		dev_warn(component->dev, "wrong device ID. expected: %u read: %u\n",
			 expected_device_id, device_id);

	/* Set device to mute */
	ret = snd_soc_component_update_bits(component, TAS5720_DIGITAL_CTRL2_REG,
				  TAS5720_MUTE, TAS5720_MUTE);
	if (ret < 0)
		goto error_snd_soc_component_update_bits;

	/*
	 * Enter shutdown mode - our default when not playing audio - to
	 * minimize current consumption. On the TAS5720 there is no real down
	 * side doing so as all device registers are preserved and the wakeup
	 * of the codec is rather quick which we do using a dapm widget.
	 */
	ret = snd_soc_component_update_bits(component, TAS5720_POWER_CTRL_REG,
				  TAS5720_SDZ, 0);
	if (ret < 0)
		goto error_snd_soc_component_update_bits;

	INIT_DELAYED_WORK(&tas5720->fault_check_work, tas5720_fault_check_work);

	return 0;

error_snd_soc_component_update_bits:
	dev_err(component->dev, "error configuring device registers: %d\n", ret);

probe_fail:
	regulator_bulk_disable(ARRAY_SIZE(tas5720->supplies),
			       tas5720->supplies);
	return ret;
}