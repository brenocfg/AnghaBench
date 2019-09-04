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
struct tps65217_bl_pdata {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct tps65217_bl_pdata *
tps65217_bl_parse_dt(struct platform_device *pdev)
{
	return NULL;
}