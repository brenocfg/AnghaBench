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
struct sh_mobile_lcdc_priv {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sh_mobile_lcdc_start (struct sh_mobile_lcdc_priv*) ; 
 struct sh_mobile_lcdc_priv* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int sh_mobile_lcdc_runtime_resume(struct device *dev)
{
	struct sh_mobile_lcdc_priv *priv = dev_get_drvdata(dev);

	__sh_mobile_lcdc_start(priv);

	return 0;
}