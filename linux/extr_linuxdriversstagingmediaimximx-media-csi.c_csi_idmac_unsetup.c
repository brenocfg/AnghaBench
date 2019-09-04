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
struct csi_priv {int /*<<< orphan*/  smfc; int /*<<< orphan*/  idmac_ch; } ;
typedef  enum vb2_buffer_state { ____Placeholder_vb2_buffer_state } vb2_buffer_state ;

/* Variables and functions */
 int /*<<< orphan*/  csi_idmac_unsetup_vb2_buf (struct csi_priv*,int) ; 
 int /*<<< orphan*/  ipu_idmac_disable_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_smfc_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csi_idmac_unsetup(struct csi_priv *priv,
			      enum vb2_buffer_state state)
{
	ipu_idmac_disable_channel(priv->idmac_ch);
	ipu_smfc_disable(priv->smfc);

	csi_idmac_unsetup_vb2_buf(priv, state);
}