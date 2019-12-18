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
struct device {int dummy; } ;
struct aic31xx_priv {int /*<<< orphan*/  regmap; scalar_t__ jack; struct device* dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int AIC31XX_ADC_OF ; 
 unsigned int AIC31XX_ADC_OF_SHIFTER ; 
 unsigned int AIC31XX_BUTTONPRESS ; 
 unsigned int AIC31XX_DAC_OF_LEFT ; 
 unsigned int AIC31XX_DAC_OF_RIGHT ; 
 unsigned int AIC31XX_DAC_OF_SHIFTER ; 
 unsigned int AIC31XX_HPLSCDETECT ; 
 unsigned int AIC31XX_HPRSCDETECT ; 
 int /*<<< orphan*/  AIC31XX_HSDETECT ; 
#define  AIC31XX_HSD_HP 129 
#define  AIC31XX_HSD_HS 128 
 unsigned int AIC31XX_HSD_TYPE_MASK ; 
 unsigned int AIC31XX_HSD_TYPE_SHIFT ; 
 unsigned int AIC31XX_HSPLUG ; 
 int /*<<< orphan*/  AIC31XX_INTRDACFLAG ; 
 int /*<<< orphan*/  AIC31XX_INTRDACFLAG2 ; 
 int /*<<< orphan*/  AIC31XX_JACK_MASK ; 
 int /*<<< orphan*/  AIC31XX_OFFLAG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_HEADPHONE ; 
 int SND_JACK_HEADSET ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  snd_soc_jack_report (scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t aic31xx_irq(int irq, void *data)
{
	struct aic31xx_priv *aic31xx = data;
	struct device *dev = aic31xx->dev;
	unsigned int value;
	bool handled = false;
	int ret;

	ret = regmap_read(aic31xx->regmap, AIC31XX_INTRDACFLAG, &value);
	if (ret) {
		dev_err(dev, "Failed to read interrupt mask: %d\n", ret);
		goto exit;
	}

	if (value)
		handled = true;
	else
		goto read_overflow;

	if (value & AIC31XX_HPLSCDETECT)
		dev_err(dev, "Short circuit on Left output is detected\n");
	if (value & AIC31XX_HPRSCDETECT)
		dev_err(dev, "Short circuit on Right output is detected\n");
	if (value & (AIC31XX_HSPLUG | AIC31XX_BUTTONPRESS)) {
		unsigned int val;
		int status = 0;

		ret = regmap_read(aic31xx->regmap, AIC31XX_INTRDACFLAG2,
				  &val);
		if (ret) {
			dev_err(dev, "Failed to read interrupt mask: %d\n",
				ret);
			goto exit;
		}

		if (val & AIC31XX_BUTTONPRESS)
			status |= SND_JACK_BTN_0;

		ret = regmap_read(aic31xx->regmap, AIC31XX_HSDETECT, &val);
		if (ret) {
			dev_err(dev, "Failed to read headset type: %d\n", ret);
			goto exit;
		}

		switch ((val & AIC31XX_HSD_TYPE_MASK) >>
			AIC31XX_HSD_TYPE_SHIFT) {
		case AIC31XX_HSD_HP:
			status |= SND_JACK_HEADPHONE;
			break;
		case AIC31XX_HSD_HS:
			status |= SND_JACK_HEADSET;
			break;
		default:
			break;
		}

		if (aic31xx->jack)
			snd_soc_jack_report(aic31xx->jack, status,
					    AIC31XX_JACK_MASK);
	}
	if (value & ~(AIC31XX_HPLSCDETECT |
		      AIC31XX_HPRSCDETECT |
		      AIC31XX_HSPLUG |
		      AIC31XX_BUTTONPRESS))
		dev_err(dev, "Unknown DAC interrupt flags: 0x%08x\n", value);

read_overflow:
	ret = regmap_read(aic31xx->regmap, AIC31XX_OFFLAG, &value);
	if (ret) {
		dev_err(dev, "Failed to read overflow flag: %d\n", ret);
		goto exit;
	}

	if (value)
		handled = true;
	else
		goto exit;

	if (value & AIC31XX_DAC_OF_LEFT)
		dev_warn(dev, "Left-channel DAC overflow has occurred\n");
	if (value & AIC31XX_DAC_OF_RIGHT)
		dev_warn(dev, "Right-channel DAC overflow has occurred\n");
	if (value & AIC31XX_DAC_OF_SHIFTER)
		dev_warn(dev, "DAC barrel shifter overflow has occurred\n");
	if (value & AIC31XX_ADC_OF)
		dev_warn(dev, "ADC overflow has occurred\n");
	if (value & AIC31XX_ADC_OF_SHIFTER)
		dev_warn(dev, "ADC barrel shifter overflow has occurred\n");
	if (value & ~(AIC31XX_DAC_OF_LEFT |
		      AIC31XX_DAC_OF_RIGHT |
		      AIC31XX_DAC_OF_SHIFTER |
		      AIC31XX_ADC_OF |
		      AIC31XX_ADC_OF_SHIFTER))
		dev_warn(dev, "Unknown overflow interrupt flags: 0x%08x\n", value);

exit:
	if (handled)
		return IRQ_HANDLED;
	else
		return IRQ_NONE;
}