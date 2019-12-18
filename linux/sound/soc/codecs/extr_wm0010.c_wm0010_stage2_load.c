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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  t ;
struct wm0010_priv {int sysclk; } ;
struct spi_transfer {int* rx_buf; int* tx_buf; int len; int bits_per_word; int speed_hz; } ;
struct spi_message {int dummy; } ;
struct spi_device {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct firmware {int size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ ) ; 
 struct wm0010_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 
 struct spi_device* to_spi_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm0010_mark_boot_failure (struct wm0010_priv*) ; 

__attribute__((used)) static int wm0010_stage2_load(struct snd_soc_component *component)
{
	struct spi_device *spi = to_spi_device(component->dev);
	struct wm0010_priv *wm0010 = snd_soc_component_get_drvdata(component);
	const struct firmware *fw;
	struct spi_message m;
	struct spi_transfer t;
	u32 *img;
	u8 *out;
	int i;
	int ret = 0;

	ret = request_firmware(&fw, "wm0010_stage2.bin", component->dev);
	if (ret != 0) {
		dev_err(component->dev, "Failed to request stage2 loader: %d\n",
			ret);
		return ret;
	}

	dev_dbg(component->dev, "Downloading %zu byte stage 2 loader\n", fw->size);

	/* Copy to local buffer first as vmalloc causes problems for dma */
	img = kzalloc(fw->size, GFP_KERNEL | GFP_DMA);
	if (!img) {
		ret = -ENOMEM;
		goto abort2;
	}

	out = kzalloc(fw->size, GFP_KERNEL | GFP_DMA);
	if (!out) {
		ret = -ENOMEM;
		goto abort1;
	}

	memcpy(img, &fw->data[0], fw->size);

	spi_message_init(&m);
	memset(&t, 0, sizeof(t));
	t.rx_buf = out;
	t.tx_buf = img;
	t.len = fw->size;
	t.bits_per_word = 8;
	t.speed_hz = wm0010->sysclk / 10;
	spi_message_add_tail(&t, &m);

	dev_dbg(component->dev, "Starting initial download at %dHz\n",
		t.speed_hz);

	ret = spi_sync(spi, &m);
	if (ret != 0) {
		dev_err(component->dev, "Initial download failed: %d\n", ret);
		goto abort;
	}

	/* Look for errors from the boot ROM */
	for (i = 0; i < fw->size; i++) {
		if (out[i] != 0x55) {
			dev_err(component->dev, "Boot ROM error: %x in %d\n",
				out[i], i);
			wm0010_mark_boot_failure(wm0010);
			ret = -EBUSY;
			goto abort;
		}
	}
abort:
	kfree(out);
abort1:
	kfree(img);
abort2:
	release_firmware(fw);

	return ret;
}