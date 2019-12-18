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
typedef  int u16 ;
struct wl1273_core {int i2s_mode; int (* write ) (struct wl1273_core*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  lock; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WL1273_AUDIO_ENABLE ; 
 int WL1273_AUDIO_ENABLE_I2S ; 
 int WL1273_I2S_DEF_MODE ; 
 int /*<<< orphan*/  WL1273_I2S_MODE_CONFIG_SET ; 
 int WL1273_IS2_RATE ; 
 int WL1273_IS2_RATE_11_025 ; 
 int WL1273_IS2_RATE_12K ; 
 int WL1273_IS2_RATE_16K ; 
 int WL1273_IS2_RATE_22_05K ; 
 int WL1273_IS2_RATE_32K ; 
 int WL1273_IS2_RATE_44_1K ; 
 int WL1273_IS2_RATE_48K ; 
 int WL1273_IS2_RATE_8K ; 
 int WL1273_IS2_WIDTH ; 
 int WL1273_IS2_WIDTH_128 ; 
 int WL1273_IS2_WIDTH_32 ; 
 int WL1273_IS2_WIDTH_40 ; 
 int WL1273_IS2_WIDTH_48 ; 
 int WL1273_IS2_WIDTH_50 ; 
 int WL1273_IS2_WIDTH_60 ; 
 int WL1273_IS2_WIDTH_64 ; 
 int WL1273_IS2_WIDTH_80 ; 
 int WL1273_IS2_WIDTH_96 ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct wl1273_core*,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct wl1273_core*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_wl1273_fm_set_i2s_mode(struct wl1273_core *core,
				      int rate, int width)
{
	struct device *dev = &core->client->dev;
	int r = 0;
	u16 mode;

	dev_dbg(dev, "rate: %d\n", rate);
	dev_dbg(dev, "width: %d\n", width);

	mutex_lock(&core->lock);

	mode = core->i2s_mode & ~WL1273_IS2_WIDTH & ~WL1273_IS2_RATE;

	switch (rate) {
	case 48000:
		mode |= WL1273_IS2_RATE_48K;
		break;
	case 44100:
		mode |= WL1273_IS2_RATE_44_1K;
		break;
	case 32000:
		mode |= WL1273_IS2_RATE_32K;
		break;
	case 22050:
		mode |= WL1273_IS2_RATE_22_05K;
		break;
	case 16000:
		mode |= WL1273_IS2_RATE_16K;
		break;
	case 12000:
		mode |= WL1273_IS2_RATE_12K;
		break;
	case 11025:
		mode |= WL1273_IS2_RATE_11_025;
		break;
	case 8000:
		mode |= WL1273_IS2_RATE_8K;
		break;
	default:
		dev_err(dev, "Sampling rate: %d not supported\n", rate);
		r = -EINVAL;
		goto out;
	}

	switch (width) {
	case 16:
		mode |= WL1273_IS2_WIDTH_32;
		break;
	case 20:
		mode |= WL1273_IS2_WIDTH_40;
		break;
	case 24:
		mode |= WL1273_IS2_WIDTH_48;
		break;
	case 25:
		mode |= WL1273_IS2_WIDTH_50;
		break;
	case 30:
		mode |= WL1273_IS2_WIDTH_60;
		break;
	case 32:
		mode |= WL1273_IS2_WIDTH_64;
		break;
	case 40:
		mode |= WL1273_IS2_WIDTH_80;
		break;
	case 48:
		mode |= WL1273_IS2_WIDTH_96;
		break;
	case 64:
		mode |= WL1273_IS2_WIDTH_128;
		break;
	default:
		dev_err(dev, "Data width: %d not supported\n", width);
		r = -EINVAL;
		goto out;
	}

	dev_dbg(dev, "WL1273_I2S_DEF_MODE: 0x%04x\n",  WL1273_I2S_DEF_MODE);
	dev_dbg(dev, "core->i2s_mode: 0x%04x\n", core->i2s_mode);
	dev_dbg(dev, "mode: 0x%04x\n", mode);

	if (core->i2s_mode != mode) {
		r = core->write(core, WL1273_I2S_MODE_CONFIG_SET, mode);
		if (r)
			goto out;

		core->i2s_mode = mode;
		r = core->write(core, WL1273_AUDIO_ENABLE,
				WL1273_AUDIO_ENABLE_I2S);
		if (r)
			goto out;
	}
out:
	mutex_unlock(&core->lock);

	return r;
}