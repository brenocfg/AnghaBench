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
struct ar8xxx_priv {int init; int /*<<< orphan*/  dev; TYPE_1__* chip; } ;
struct TYPE_2__ {int (* hw_init ) (struct ar8xxx_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ar8xxx_mib_start (struct ar8xxx_priv*) ; 
 int ar8xxx_sw_reset_switch (int /*<<< orphan*/ *) ; 
 int stub1 (struct ar8xxx_priv*) ; 

__attribute__((used)) static int
ar8xxx_start(struct ar8xxx_priv *priv)
{
	int ret;

	priv->init = true;

	ret = priv->chip->hw_init(priv);
	if (ret)
		return ret;

	ret = ar8xxx_sw_reset_switch(&priv->dev);
	if (ret)
		return ret;

	priv->init = false;

	ar8xxx_mib_start(priv);

	return 0;
}