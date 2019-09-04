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
struct esp {int sreg; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_STATUS ; 
 int ESP_STAT_INTR ; 
 struct zorro_esp_priv* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int zorro_esp_read8 (struct esp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int zorro_esp_wait_for_intr(struct esp *esp)
{
	struct zorro_esp_priv *zep = dev_get_drvdata(esp->dev);
	int i = 500000;

	do {
		esp->sreg = zorro_esp_read8(esp, ESP_STATUS);
		if (esp->sreg & ESP_STAT_INTR)
			return 0;

		udelay(2);
	} while (--i);

	pr_err("IRQ timeout (sreg %02x)\n", esp->sreg);
	zep->error = 1;
	return 1;
}