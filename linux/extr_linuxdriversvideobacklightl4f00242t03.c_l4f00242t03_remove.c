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
struct spi_device {int dummy; } ;
struct l4f00242t03_priv {int /*<<< orphan*/  ld; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  l4f00242t03_lcd_power_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct l4f00242t03_priv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int l4f00242t03_remove(struct spi_device *spi)
{
	struct l4f00242t03_priv *priv = spi_get_drvdata(spi);

	l4f00242t03_lcd_power_set(priv->ld, FB_BLANK_POWERDOWN);
	return 0;
}