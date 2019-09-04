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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ CR_RANGE (int /*<<< orphan*/ ) ; 
 int S626_GPIO1_HI ; 
 scalar_t__ S626_GSEL_BIPOLAR10V ; 
 scalar_t__ S626_GSEL_BIPOLAR5V ; 
 int /*<<< orphan*/  S626_LP_GSEL ; 
 int /*<<< orphan*/  S626_LP_ISEL ; 
 scalar_t__ S626_P_FB_BUFFER1 ; 
 scalar_t__ S626_P_GPIO ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  s626_ai_eoc ; 
 unsigned int s626_ai_reg_to_uint (int) ; 
 int /*<<< orphan*/  s626_debi_write (struct comedi_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int s626_ai_insn_read(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     struct comedi_insn *insn,
			     unsigned int *data)
{
	u16 chan = CR_CHAN(insn->chanspec);
	u16 range = CR_RANGE(insn->chanspec);
	u16 adc_spec = 0;
	u32 gpio_image;
	u32 tmp;
	int ret;
	int n;

	/*
	 * Convert application's ADC specification into form
	 *  appropriate for register programming.
	 */
	if (range == 0)
		adc_spec = (chan << 8) | (S626_GSEL_BIPOLAR5V);
	else
		adc_spec = (chan << 8) | (S626_GSEL_BIPOLAR10V);

	/* Switch ADC analog gain. */
	s626_debi_write(dev, S626_LP_GSEL, adc_spec);	/* Set gain. */

	/* Select ADC analog input channel. */
	s626_debi_write(dev, S626_LP_ISEL, adc_spec);	/* Select channel. */

	for (n = 0; n < insn->n; n++) {
		/* Delay 10 microseconds for analog input settling. */
		usleep_range(10, 20);

		/* Start ADC by pulsing GPIO1 low */
		gpio_image = readl(dev->mmio + S626_P_GPIO);
		/* Assert ADC Start command */
		writel(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
		/* and stretch it out */
		writel(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
		writel(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
		/* Negate ADC Start command */
		writel(gpio_image | S626_GPIO1_HI, dev->mmio + S626_P_GPIO);

		/*
		 * Wait for ADC to complete (GPIO2 is asserted high when
		 * ADC not busy) and for data from previous conversion to
		 * shift into FB BUFFER 1 register.
		 */

		/* Wait for ADC done */
		ret = comedi_timeout(dev, s, insn, s626_ai_eoc, 0);
		if (ret)
			return ret;

		/* Fetch ADC data */
		if (n != 0) {
			tmp = readl(dev->mmio + S626_P_FB_BUFFER1);
			data[n - 1] = s626_ai_reg_to_uint(tmp);
		}

		/*
		 * Allow the ADC to stabilize for 4 microseconds before
		 * starting the next (final) conversion.  This delay is
		 * necessary to allow sufficient time between last
		 * conversion finished and the start of the next
		 * conversion.  Without this delay, the last conversion's
		 * data value is sometimes set to the previous
		 * conversion's data value.
		 */
		udelay(4);
	}

	/*
	 * Start a dummy conversion to cause the data from the
	 * previous conversion to be shifted in.
	 */
	gpio_image = readl(dev->mmio + S626_P_GPIO);
	/* Assert ADC Start command */
	writel(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
	/* and stretch it out */
	writel(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
	writel(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
	/* Negate ADC Start command */
	writel(gpio_image | S626_GPIO1_HI, dev->mmio + S626_P_GPIO);

	/* Wait for the data to arrive in FB BUFFER 1 register. */

	/* Wait for ADC done */
	ret = comedi_timeout(dev, s, insn, s626_ai_eoc, 0);
	if (ret)
		return ret;

	/* Fetch ADC data from audio interface's input shift register. */

	/* Fetch ADC data */
	if (n != 0) {
		tmp = readl(dev->mmio + S626_P_FB_BUFFER1);
		data[n - 1] = s626_ai_reg_to_uint(tmp);
	}

	return n;
}