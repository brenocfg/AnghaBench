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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e750_audio_gpios ; 
 int /*<<< orphan*/  gpio_free_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int e750_remove(struct platform_device *pdev)
{
	gpio_free_array(e750_audio_gpios, ARRAY_SIZE(e750_audio_gpios));
	return 0;
}