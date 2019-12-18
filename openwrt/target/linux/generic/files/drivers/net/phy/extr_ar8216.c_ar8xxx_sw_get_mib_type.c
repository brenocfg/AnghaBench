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
struct TYPE_2__ {int /*<<< orphan*/  i; } ;
struct switch_val {TYPE_1__ value; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct ar8xxx_priv {int /*<<< orphan*/  mib_type; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ar8xxx_has_mib_counters (struct ar8xxx_priv*) ; 
 struct ar8xxx_priv* swdev_to_ar8xxx (struct switch_dev*) ; 

int
ar8xxx_sw_get_mib_type(struct switch_dev *dev,
			       const struct switch_attr *attr,
			       struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);

	if (!ar8xxx_has_mib_counters(priv))
		return -EOPNOTSUPP;
	val->value.i = priv->mib_type;
	return 0;
}