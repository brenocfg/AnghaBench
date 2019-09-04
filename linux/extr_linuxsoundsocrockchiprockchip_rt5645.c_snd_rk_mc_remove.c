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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * codec_of_node; int /*<<< orphan*/ * cpu_of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ *) ; 
 TYPE_1__ rk_dailink ; 

__attribute__((used)) static int snd_rk_mc_remove(struct platform_device *pdev)
{
	of_node_put(rk_dailink.cpu_of_node);
	rk_dailink.cpu_of_node = NULL;
	of_node_put(rk_dailink.codec_of_node);
	rk_dailink.codec_of_node = NULL;

	return 0;
}