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
struct rcar_thermal_priv {int ctemp; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int MCELSIUS (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct device* rcar_priv_to_dev (struct rcar_thermal_priv*) ; 
 int rcar_thermal_update_temp (struct rcar_thermal_priv*) ; 

__attribute__((used)) static int rcar_thermal_get_current_temp(struct rcar_thermal_priv *priv,
					 int *temp)
{
	int tmp;
	int ret;

	ret = rcar_thermal_update_temp(priv);
	if (ret < 0)
		return ret;

	mutex_lock(&priv->lock);
	tmp =  MCELSIUS((priv->ctemp * 5) - 65);
	mutex_unlock(&priv->lock);

	if ((tmp < MCELSIUS(-45)) || (tmp > MCELSIUS(125))) {
		struct device *dev = rcar_priv_to_dev(priv);

		dev_err(dev, "it couldn't measure temperature correctly\n");
		return -EIO;
	}

	*temp = tmp;

	return 0;
}