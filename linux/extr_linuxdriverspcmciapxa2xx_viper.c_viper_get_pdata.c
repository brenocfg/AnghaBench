#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct arcom_pcmcia_pdata {int dummy; } ;
struct TYPE_3__ {struct arcom_pcmcia_pdata* platform_data; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 TYPE_2__* arcom_pcmcia_dev ; 

__attribute__((used)) static inline struct arcom_pcmcia_pdata *viper_get_pdata(void)
{
	return arcom_pcmcia_dev->dev.platform_data;
}