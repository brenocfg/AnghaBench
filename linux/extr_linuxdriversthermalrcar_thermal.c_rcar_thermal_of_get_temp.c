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
struct rcar_thermal_priv {int dummy; } ;

/* Variables and functions */
 int rcar_thermal_get_current_temp (struct rcar_thermal_priv*,int*) ; 

__attribute__((used)) static int rcar_thermal_of_get_temp(void *data, int *temp)
{
	struct rcar_thermal_priv *priv = data;

	return rcar_thermal_get_current_temp(priv, temp);
}