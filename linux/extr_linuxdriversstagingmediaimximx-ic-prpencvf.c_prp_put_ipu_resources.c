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
struct prp_priv {int /*<<< orphan*/ * rot_out_ch; int /*<<< orphan*/ * rot_in_ch; int /*<<< orphan*/ * out_ch; int /*<<< orphan*/ * ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipu_ic_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipu_idmac_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prp_put_ipu_resources(struct prp_priv *priv)
{
	if (priv->ic)
		ipu_ic_put(priv->ic);
	priv->ic = NULL;

	if (priv->out_ch)
		ipu_idmac_put(priv->out_ch);
	priv->out_ch = NULL;

	if (priv->rot_in_ch)
		ipu_idmac_put(priv->rot_in_ch);
	priv->rot_in_ch = NULL;

	if (priv->rot_out_ch)
		ipu_idmac_put(priv->rot_out_ch);
	priv->rot_out_ch = NULL;
}