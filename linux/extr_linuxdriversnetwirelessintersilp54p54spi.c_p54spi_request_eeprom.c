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
struct p54s_priv {TYPE_1__* spi; } ;
struct ieee80211_hw {struct p54s_priv* priv; } ;
struct firmware {scalar_t__ size; scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int p54_parse_eeprom (struct ieee80211_hw*,void*,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware_direct (struct firmware const**,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int p54spi_request_eeprom(struct ieee80211_hw *dev)
{
	struct p54s_priv *priv = dev->priv;
	const struct firmware *eeprom;
	int ret;

	/* allow users to customize their eeprom.
	 */

	ret = request_firmware_direct(&eeprom, "3826.eeprom", &priv->spi->dev);
	if (ret < 0) {
#ifdef CONFIG_P54_SPI_DEFAULT_EEPROM
		dev_info(&priv->spi->dev, "loading default eeprom...\n");
		ret = p54_parse_eeprom(dev, (void *) p54spi_eeprom,
				       sizeof(p54spi_eeprom));
#else
		dev_err(&priv->spi->dev, "Failed to request user eeprom\n");
#endif /* CONFIG_P54_SPI_DEFAULT_EEPROM */
	} else {
		dev_info(&priv->spi->dev, "loading user eeprom...\n");
		ret = p54_parse_eeprom(dev, (void *) eeprom->data,
				       (int)eeprom->size);
		release_firmware(eeprom);
	}
	return ret;
}