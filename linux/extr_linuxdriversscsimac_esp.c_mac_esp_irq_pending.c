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
struct esp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_STATUS ; 
 int ESP_STAT_INTR ; 
 int esp_read8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mac_esp_irq_pending(struct esp *esp)
{
	if (esp_read8(ESP_STATUS) & ESP_STAT_INTR)
		return 1;
	return 0;
}