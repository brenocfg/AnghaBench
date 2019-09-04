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
struct zorro_esp_priv {int error; } ;
struct esp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct zorro_esp_priv* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zorro_esp_dma_error(struct esp *esp)
{
	struct zorro_esp_priv *zep = dev_get_drvdata(esp->dev);

	/* check for error in case we've been doing PIO */
	if (zep->error == 1)
		return 1;

	/* do nothing - there seems to be no way to check for DMA errors */
	return 0;
}