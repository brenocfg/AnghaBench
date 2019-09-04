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
typedef  int u32 ;
struct rcar_thermal_priv {int /*<<< orphan*/  id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,char*,char*) ; 
 int rcar_id_to_shift (struct rcar_thermal_priv*) ; 
 struct device* rcar_priv_to_dev (struct rcar_thermal_priv*) ; 

__attribute__((used)) static u32 rcar_thermal_had_changed(struct rcar_thermal_priv *priv, u32 status)
{
	struct device *dev = rcar_priv_to_dev(priv);

	status = (status >> rcar_id_to_shift(priv)) & 0x3;

	if (status) {
		dev_dbg(dev, "thermal%d %s%s\n",
			priv->id,
			(status & 0x2) ? "Rising " : "",
			(status & 0x1) ? "Falling" : "");
	}

	return status;
}