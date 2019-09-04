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
struct TYPE_2__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct at91_rtc_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  at91_rtc_dt_ids ; 
 struct at91_rtc_config const at91rm9200_config ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static const struct at91_rtc_config *
at91_rtc_get_config(struct platform_device *pdev)
{
	const struct of_device_id *match;

	if (pdev->dev.of_node) {
		match = of_match_node(at91_rtc_dt_ids, pdev->dev.of_node);
		if (!match)
			return NULL;
		return (const struct at91_rtc_config *)match->data;
	}

	return &at91rm9200_config;
}