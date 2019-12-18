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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  t ;
struct wm0010_priv {scalar_t__ state; int sysclk; int pll_running; int /*<<< orphan*/  core_supplies; int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  pll_clkctrl1; scalar_t__ max_spi_freq; int /*<<< orphan*/  boot_completion; int /*<<< orphan*/  gpio_reset_value; int /*<<< orphan*/  gpio_reset; int /*<<< orphan*/  dbvdd; int /*<<< orphan*/  dev; } ;
struct spi_transfer {int length; int len; int bits_per_word; int speed_hz; int /*<<< orphan*/ * tx_buf; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/  clkctrl1; int /*<<< orphan*/  command; } ;
struct spi_message {int dummy; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct snd_soc_component {int /*<<< orphan*/ * dev; } ;
struct dfw_pllrec {int length; int len; int bits_per_word; int speed_hz; int /*<<< orphan*/ * tx_buf; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/  clkctrl1; int /*<<< orphan*/  command; } ;
typedef  int /*<<< orphan*/  pll_rec ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFW_CMD_PLL ; 
 int ECANCELED ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 scalar_t__ WM0010_BOOTROM ; 
 scalar_t__ WM0010_FIRMWARE ; 
 scalar_t__ WM0010_OUT_OF_RESET ; 
 scalar_t__ WM0010_POWER_OFF ; 
 scalar_t__ WM0010_STAGE2 ; 
 int /*<<< orphan*/  byte_swap_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 struct wm0010_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct spi_device* to_spi_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wm0010_firmware_load (char*,struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm0010_halt (struct snd_soc_component*) ; 
 int wm0010_stage2_load (struct snd_soc_component*) ; 

__attribute__((used)) static int wm0010_boot(struct snd_soc_component *component)
{
	struct spi_device *spi = to_spi_device(component->dev);
	struct wm0010_priv *wm0010 = snd_soc_component_get_drvdata(component);
	unsigned long flags;
	int ret;
	struct spi_message m;
	struct spi_transfer t;
	struct dfw_pllrec pll_rec;
	u32 *p, len;
	u64 *img_swap;
	u8 *out;
	int i;

	spin_lock_irqsave(&wm0010->irq_lock, flags);
	if (wm0010->state != WM0010_POWER_OFF)
		dev_warn(wm0010->dev, "DSP already powered up!\n");
	spin_unlock_irqrestore(&wm0010->irq_lock, flags);

	if (wm0010->sysclk > 26000000) {
		dev_err(component->dev, "Max DSP clock frequency is 26MHz\n");
		ret = -ECANCELED;
		goto err;
	}

	mutex_lock(&wm0010->lock);
	wm0010->pll_running = false;

	dev_dbg(component->dev, "max_spi_freq: %d\n", wm0010->max_spi_freq);

	ret = regulator_bulk_enable(ARRAY_SIZE(wm0010->core_supplies),
				    wm0010->core_supplies);
	if (ret != 0) {
		dev_err(&spi->dev, "Failed to enable core supplies: %d\n",
			ret);
		mutex_unlock(&wm0010->lock);
		goto err;
	}

	ret = regulator_enable(wm0010->dbvdd);
	if (ret != 0) {
		dev_err(&spi->dev, "Failed to enable DBVDD: %d\n", ret);
		goto err_core;
	}

	/* Release reset */
	gpio_set_value_cansleep(wm0010->gpio_reset, !wm0010->gpio_reset_value);
	spin_lock_irqsave(&wm0010->irq_lock, flags);
	wm0010->state = WM0010_OUT_OF_RESET;
	spin_unlock_irqrestore(&wm0010->irq_lock, flags);

	if (!wait_for_completion_timeout(&wm0010->boot_completion,
					 msecs_to_jiffies(20)))
		dev_err(component->dev, "Failed to get interrupt from DSP\n");

	spin_lock_irqsave(&wm0010->irq_lock, flags);
	wm0010->state = WM0010_BOOTROM;
	spin_unlock_irqrestore(&wm0010->irq_lock, flags);

	ret = wm0010_stage2_load(component);
	if (ret)
		goto abort;

	if (!wait_for_completion_timeout(&wm0010->boot_completion,
					 msecs_to_jiffies(20)))
		dev_err(component->dev, "Failed to get interrupt from DSP loader.\n");

	spin_lock_irqsave(&wm0010->irq_lock, flags);
	wm0010->state = WM0010_STAGE2;
	spin_unlock_irqrestore(&wm0010->irq_lock, flags);

	/* Only initialise PLL if max_spi_freq initialised */
	if (wm0010->max_spi_freq) {

		/* Initialise a PLL record */
		memset(&pll_rec, 0, sizeof(pll_rec));
		pll_rec.command = DFW_CMD_PLL;
		pll_rec.length = (sizeof(pll_rec) - 8);

		/* On wm0010 only the CLKCTRL1 value is used */
		pll_rec.clkctrl1 = wm0010->pll_clkctrl1;

		ret = -ENOMEM;
		len = pll_rec.length + 8;
		out = kzalloc(len, GFP_KERNEL | GFP_DMA);
		if (!out)
			goto abort;

		img_swap = kzalloc(len, GFP_KERNEL | GFP_DMA);
		if (!img_swap)
			goto abort_out;

		/* We need to re-order for 0010 */
		byte_swap_64((u64 *)&pll_rec, img_swap, len);

		spi_message_init(&m);
		memset(&t, 0, sizeof(t));
		t.rx_buf = out;
		t.tx_buf = img_swap;
		t.len = len;
		t.bits_per_word = 8;
		t.speed_hz = wm0010->sysclk / 6;
		spi_message_add_tail(&t, &m);

		ret = spi_sync(spi, &m);
		if (ret) {
			dev_err(component->dev, "First PLL write failed: %d\n", ret);
			goto abort_swap;
		}

		/* Use a second send of the message to get the return status */
		ret = spi_sync(spi, &m);
		if (ret) {
			dev_err(component->dev, "Second PLL write failed: %d\n", ret);
			goto abort_swap;
		}

		p = (u32 *)out;

		/* Look for PLL active code from the DSP */
		for (i = 0; i < len / 4; i++) {
			if (*p == 0x0e00ed0f) {
				dev_dbg(component->dev, "PLL packet received\n");
				wm0010->pll_running = true;
				break;
			}
			p++;
		}

		kfree(img_swap);
		kfree(out);
	} else
		dev_dbg(component->dev, "Not enabling DSP PLL.");

	ret = wm0010_firmware_load("wm0010.dfw", component);

	if (ret != 0)
		goto abort;

	spin_lock_irqsave(&wm0010->irq_lock, flags);
	wm0010->state = WM0010_FIRMWARE;
	spin_unlock_irqrestore(&wm0010->irq_lock, flags);

	mutex_unlock(&wm0010->lock);

	return 0;

abort_swap:
	kfree(img_swap);
abort_out:
	kfree(out);
abort:
	/* Put the chip back into reset */
	wm0010_halt(component);
	mutex_unlock(&wm0010->lock);
	return ret;

err_core:
	mutex_unlock(&wm0010->lock);
	regulator_bulk_disable(ARRAY_SIZE(wm0010->core_supplies),
			       wm0010->core_supplies);
err:
	return ret;
}