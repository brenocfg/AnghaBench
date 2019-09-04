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
 int /*<<< orphan*/  _LDCNT1R ; 
 struct sh_mobile_lcdc_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  lcdc_write (struct sh_mobile_lcdc_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_mobile_lcdc_runtime_suspend(struct device *dev)
{
	struct sh_mobile_lcdc_priv *priv = dev_get_drvdata(dev);

	/* turn off LCDC hardware */
	lcdc_write(priv, _LDCNT1R, 0);

	return 0;
}