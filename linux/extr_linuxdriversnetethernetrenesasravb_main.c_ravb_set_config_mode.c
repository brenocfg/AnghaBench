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
struct ravb_private {scalar_t__ chip_id; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCC ; 
 int /*<<< orphan*/  CCC_CSEL ; 
 int CCC_CSEL_HPB ; 
 int CCC_GAC ; 
 int /*<<< orphan*/  CCC_OPC ; 
 int CCC_OPC_CONFIG ; 
 scalar_t__ RCAR_GEN2 ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ravb_modify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ravb_set_config_mode(struct net_device *ndev)
{
	struct ravb_private *priv = netdev_priv(ndev);

	if (priv->chip_id == RCAR_GEN2) {
		ravb_modify(ndev, CCC, CCC_OPC, CCC_OPC_CONFIG);
		/* Set CSEL value */
		ravb_modify(ndev, CCC, CCC_CSEL, CCC_CSEL_HPB);
	} else {
		ravb_modify(ndev, CCC, CCC_OPC, CCC_OPC_CONFIG |
			    CCC_GAC | CCC_CSEL_HPB);
	}
}