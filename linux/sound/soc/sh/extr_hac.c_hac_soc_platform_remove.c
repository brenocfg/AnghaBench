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
 int /*<<< orphan*/  snd_soc_set_ac97_ops (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hac_soc_platform_remove(struct platform_device *pdev)
{
	snd_soc_set_ac97_ops(NULL);
	return 0;
}