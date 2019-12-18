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
struct i2c_client {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct cs42l42_private {unsigned int ts_inv; unsigned int ts_dbnc_rise; unsigned int ts_dbnc_fall; unsigned int btn_det_init_dbnce; unsigned int btn_det_event_dbnce; unsigned int* bias_thresholds; unsigned int hs_bias_ramp_rate; int /*<<< orphan*/  regmap; void* hs_bias_ramp_time; } ;

/* Variables and functions */
 void* CS42L42_BTN_DET_EVENT_DBNCE_DEFAULT ; 
 unsigned int CS42L42_BTN_DET_EVENT_DBNCE_MAX ; 
 unsigned int CS42L42_BTN_DET_EVENT_DBNCE_MIN ; 
 void* CS42L42_BTN_DET_INIT_DBNCE_DEFAULT ; 
 unsigned int CS42L42_BTN_DET_INIT_DBNCE_MAX ; 
 unsigned int CS42L42_BTN_DET_INIT_DBNCE_MIN ; 
#define  CS42L42_HSBIAS_RAMP_FAST 141 
#define  CS42L42_HSBIAS_RAMP_FAST_RISE_SLOW_FALL 140 
 int /*<<< orphan*/  CS42L42_HSBIAS_RAMP_MASK ; 
 int CS42L42_HSBIAS_RAMP_SHIFT ; 
#define  CS42L42_HSBIAS_RAMP_SLOW 139 
#define  CS42L42_HSBIAS_RAMP_SLOWEST 138 
 void* CS42L42_HSBIAS_RAMP_TIME0 ; 
 void* CS42L42_HSBIAS_RAMP_TIME1 ; 
 void* CS42L42_HSBIAS_RAMP_TIME2 ; 
 void* CS42L42_HSBIAS_RAMP_TIME3 ; 
 int /*<<< orphan*/  CS42L42_HS_BIAS_CTL ; 
 unsigned int CS42L42_HS_DET_LEVEL_MAX ; 
 unsigned int CS42L42_HS_DET_LEVEL_MIN ; 
 int CS42L42_NUM_BIASES ; 
 int /*<<< orphan*/  CS42L42_TSENSE_CTL ; 
#define  CS42L42_TS_DBNCE_0 137 
#define  CS42L42_TS_DBNCE_1000 136 
#define  CS42L42_TS_DBNCE_125 135 
#define  CS42L42_TS_DBNCE_1250 134 
#define  CS42L42_TS_DBNCE_1500 133 
#define  CS42L42_TS_DBNCE_250 132 
#define  CS42L42_TS_DBNCE_500 131 
#define  CS42L42_TS_DBNCE_750 130 
 int /*<<< orphan*/  CS42L42_TS_FALL_DBNCE_TIME_MASK ; 
 int CS42L42_TS_FALL_DBNCE_TIME_SHIFT ; 
#define  CS42L42_TS_INV_DIS 129 
#define  CS42L42_TS_INV_EN 128 
 int /*<<< orphan*/  CS42L42_TS_INV_MASK ; 
 int CS42L42_TS_INV_SHIFT ; 
 int /*<<< orphan*/  CS42L42_TS_RISE_DBNCE_TIME_MASK ; 
 int CS42L42_TS_RISE_DBNCE_TIME_SHIFT ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,unsigned int,...) ; 
 int of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 
 int of_property_read_u32_array (struct device_node*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void** threshold_defaults ; 

__attribute__((used)) static int cs42l42_handle_device_data(struct i2c_client *i2c_client,
					struct cs42l42_private *cs42l42)
{
	struct device_node *np = i2c_client->dev.of_node;
	unsigned int val;
	unsigned int thresholds[CS42L42_NUM_BIASES];
	int ret;
	int i;

	ret = of_property_read_u32(np, "cirrus,ts-inv", &val);

	if (!ret) {
		switch (val) {
		case CS42L42_TS_INV_EN:
		case CS42L42_TS_INV_DIS:
			cs42l42->ts_inv = val;
			break;
		default:
			dev_err(&i2c_client->dev,
				"Wrong cirrus,ts-inv DT value %d\n",
				val);
			cs42l42->ts_inv = CS42L42_TS_INV_DIS;
		}
	} else {
		cs42l42->ts_inv = CS42L42_TS_INV_DIS;
	}

	regmap_update_bits(cs42l42->regmap, CS42L42_TSENSE_CTL,
			CS42L42_TS_INV_MASK,
			(cs42l42->ts_inv << CS42L42_TS_INV_SHIFT));

	ret = of_property_read_u32(np, "cirrus,ts-dbnc-rise", &val);

	if (!ret) {
		switch (val) {
		case CS42L42_TS_DBNCE_0:
		case CS42L42_TS_DBNCE_125:
		case CS42L42_TS_DBNCE_250:
		case CS42L42_TS_DBNCE_500:
		case CS42L42_TS_DBNCE_750:
		case CS42L42_TS_DBNCE_1000:
		case CS42L42_TS_DBNCE_1250:
		case CS42L42_TS_DBNCE_1500:
			cs42l42->ts_dbnc_rise = val;
			break;
		default:
			dev_err(&i2c_client->dev,
				"Wrong cirrus,ts-dbnc-rise DT value %d\n",
				val);
			cs42l42->ts_dbnc_rise = CS42L42_TS_DBNCE_1000;
		}
	} else {
		cs42l42->ts_dbnc_rise = CS42L42_TS_DBNCE_1000;
	}

	regmap_update_bits(cs42l42->regmap, CS42L42_TSENSE_CTL,
			CS42L42_TS_RISE_DBNCE_TIME_MASK,
			(cs42l42->ts_dbnc_rise <<
			CS42L42_TS_RISE_DBNCE_TIME_SHIFT));

	ret = of_property_read_u32(np, "cirrus,ts-dbnc-fall", &val);

	if (!ret) {
		switch (val) {
		case CS42L42_TS_DBNCE_0:
		case CS42L42_TS_DBNCE_125:
		case CS42L42_TS_DBNCE_250:
		case CS42L42_TS_DBNCE_500:
		case CS42L42_TS_DBNCE_750:
		case CS42L42_TS_DBNCE_1000:
		case CS42L42_TS_DBNCE_1250:
		case CS42L42_TS_DBNCE_1500:
			cs42l42->ts_dbnc_fall = val;
			break;
		default:
			dev_err(&i2c_client->dev,
				"Wrong cirrus,ts-dbnc-fall DT value %d\n",
				val);
			cs42l42->ts_dbnc_fall = CS42L42_TS_DBNCE_0;
		}
	} else {
		cs42l42->ts_dbnc_fall = CS42L42_TS_DBNCE_0;
	}

	regmap_update_bits(cs42l42->regmap, CS42L42_TSENSE_CTL,
			CS42L42_TS_FALL_DBNCE_TIME_MASK,
			(cs42l42->ts_dbnc_fall <<
			CS42L42_TS_FALL_DBNCE_TIME_SHIFT));

	ret = of_property_read_u32(np, "cirrus,btn-det-init-dbnce", &val);

	if (!ret) {
		if ((val >= CS42L42_BTN_DET_INIT_DBNCE_MIN) &&
			(val <= CS42L42_BTN_DET_INIT_DBNCE_MAX))
			cs42l42->btn_det_init_dbnce = val;
		else {
			dev_err(&i2c_client->dev,
				"Wrong cirrus,btn-det-init-dbnce DT value %d\n",
				val);
			cs42l42->btn_det_init_dbnce =
				CS42L42_BTN_DET_INIT_DBNCE_DEFAULT;
		}
	} else {
		cs42l42->btn_det_init_dbnce =
			CS42L42_BTN_DET_INIT_DBNCE_DEFAULT;
	}

	ret = of_property_read_u32(np, "cirrus,btn-det-event-dbnce", &val);

	if (!ret) {
		if ((val >= CS42L42_BTN_DET_EVENT_DBNCE_MIN) &&
			(val <= CS42L42_BTN_DET_EVENT_DBNCE_MAX))
			cs42l42->btn_det_event_dbnce = val;
		else {
			dev_err(&i2c_client->dev,
			"Wrong cirrus,btn-det-event-dbnce DT value %d\n", val);
			cs42l42->btn_det_event_dbnce =
				CS42L42_BTN_DET_EVENT_DBNCE_DEFAULT;
		}
	} else {
		cs42l42->btn_det_event_dbnce =
			CS42L42_BTN_DET_EVENT_DBNCE_DEFAULT;
	}

	ret = of_property_read_u32_array(np, "cirrus,bias-lvls",
				   (u32 *)thresholds, CS42L42_NUM_BIASES);

	if (!ret) {
		for (i = 0; i < CS42L42_NUM_BIASES; i++) {
			if ((thresholds[i] >= CS42L42_HS_DET_LEVEL_MIN) &&
				(thresholds[i] <= CS42L42_HS_DET_LEVEL_MAX))
				cs42l42->bias_thresholds[i] = thresholds[i];
			else {
				dev_err(&i2c_client->dev,
				"Wrong cirrus,bias-lvls[%d] DT value %d\n", i,
					thresholds[i]);
				cs42l42->bias_thresholds[i] =
					threshold_defaults[i];
			}
		}
	} else {
		for (i = 0; i < CS42L42_NUM_BIASES; i++)
			cs42l42->bias_thresholds[i] = threshold_defaults[i];
	}

	ret = of_property_read_u32(np, "cirrus,hs-bias-ramp-rate", &val);

	if (!ret) {
		switch (val) {
		case CS42L42_HSBIAS_RAMP_FAST_RISE_SLOW_FALL:
			cs42l42->hs_bias_ramp_rate = val;
			cs42l42->hs_bias_ramp_time = CS42L42_HSBIAS_RAMP_TIME0;
			break;
		case CS42L42_HSBIAS_RAMP_FAST:
			cs42l42->hs_bias_ramp_rate = val;
			cs42l42->hs_bias_ramp_time = CS42L42_HSBIAS_RAMP_TIME1;
			break;
		case CS42L42_HSBIAS_RAMP_SLOW:
			cs42l42->hs_bias_ramp_rate = val;
			cs42l42->hs_bias_ramp_time = CS42L42_HSBIAS_RAMP_TIME2;
			break;
		case CS42L42_HSBIAS_RAMP_SLOWEST:
			cs42l42->hs_bias_ramp_rate = val;
			cs42l42->hs_bias_ramp_time = CS42L42_HSBIAS_RAMP_TIME3;
			break;
		default:
			dev_err(&i2c_client->dev,
				"Wrong cirrus,hs-bias-ramp-rate DT value %d\n",
				val);
			cs42l42->hs_bias_ramp_rate = CS42L42_HSBIAS_RAMP_SLOW;
			cs42l42->hs_bias_ramp_time = CS42L42_HSBIAS_RAMP_TIME2;
		}
	} else {
		cs42l42->hs_bias_ramp_rate = CS42L42_HSBIAS_RAMP_SLOW;
		cs42l42->hs_bias_ramp_time = CS42L42_HSBIAS_RAMP_TIME2;
	}

	regmap_update_bits(cs42l42->regmap, CS42L42_HS_BIAS_CTL,
			CS42L42_HSBIAS_RAMP_MASK,
			(cs42l42->hs_bias_ramp_rate <<
			CS42L42_HSBIAS_RAMP_SHIFT));

	return 0;
}