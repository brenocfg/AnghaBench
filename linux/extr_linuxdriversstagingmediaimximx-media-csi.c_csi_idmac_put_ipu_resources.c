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
struct csi_priv {int /*<<< orphan*/ * smfc; int /*<<< orphan*/ * idmac_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipu_idmac_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipu_smfc_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void csi_idmac_put_ipu_resources(struct csi_priv *priv)
{
	if (priv->idmac_ch)
		ipu_idmac_put(priv->idmac_ch);
	priv->idmac_ch = NULL;

	if (priv->smfc)
		ipu_smfc_put(priv->smfc);
	priv->smfc = NULL;
}