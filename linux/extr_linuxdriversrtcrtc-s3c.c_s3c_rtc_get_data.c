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
struct s3c_rtc_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {struct s3c_rtc_data const* data; } ;

/* Variables and functions */
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_rtc_dt_match ; 

__attribute__((used)) static const struct s3c_rtc_data *s3c_rtc_get_data(struct platform_device *pdev)
{
	const struct of_device_id *match;

	match = of_match_node(s3c_rtc_dt_match, pdev->dev.of_node);
	return match->data;
}