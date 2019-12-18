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
struct mtk_base_afe {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mtk_base_afe* dev_get_drvdata (struct device*) ; 
 int mt2701_afe_enable_clock (struct mtk_base_afe*) ; 

__attribute__((used)) static int mt2701_afe_runtime_resume(struct device *dev)
{
	struct mtk_base_afe *afe = dev_get_drvdata(dev);

	return mt2701_afe_enable_clock(afe);
}