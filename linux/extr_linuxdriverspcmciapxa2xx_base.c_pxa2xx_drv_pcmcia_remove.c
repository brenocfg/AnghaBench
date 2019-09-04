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
struct skt_dev_info {int nskt; int /*<<< orphan*/ * skt; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct skt_dev_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  soc_pcmcia_remove_one (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pxa2xx_drv_pcmcia_remove(struct platform_device *dev)
{
	struct skt_dev_info *sinfo = platform_get_drvdata(dev);
	int i;

	for (i = 0; i < sinfo->nskt; i++)
		soc_pcmcia_remove_one(&sinfo->skt[i]);

	return 0;
}