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
struct platform_device {int dummy; } ;
struct esp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  esp_get_bursts (struct esp*,struct platform_device*) ; 
 int /*<<< orphan*/  esp_get_clock_params (struct esp*) ; 
 int /*<<< orphan*/  esp_get_differential (struct esp*) ; 
 int /*<<< orphan*/  esp_get_scsi_id (struct esp*,struct platform_device*) ; 

__attribute__((used)) static void esp_sbus_get_props(struct esp *esp, struct platform_device *espdma)
{
	esp_get_scsi_id(esp, espdma);
	esp_get_differential(esp);
	esp_get_clock_params(esp);
	esp_get_bursts(esp, espdma);
}