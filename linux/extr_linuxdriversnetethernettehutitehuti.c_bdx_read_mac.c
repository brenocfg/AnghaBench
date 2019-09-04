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
typedef  int u16 ;
struct bdx_priv {TYPE_1__* ndev; } ;
struct TYPE_2__ {int* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int READ_REG (struct bdx_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regUNC_MAC0_A ; 
 int /*<<< orphan*/  regUNC_MAC1_A ; 
 int /*<<< orphan*/  regUNC_MAC2_A ; 

__attribute__((used)) static int bdx_read_mac(struct bdx_priv *priv)
{
	u16 macAddress[3], i;
	ENTER;

	macAddress[2] = READ_REG(priv, regUNC_MAC0_A);
	macAddress[2] = READ_REG(priv, regUNC_MAC0_A);
	macAddress[1] = READ_REG(priv, regUNC_MAC1_A);
	macAddress[1] = READ_REG(priv, regUNC_MAC1_A);
	macAddress[0] = READ_REG(priv, regUNC_MAC2_A);
	macAddress[0] = READ_REG(priv, regUNC_MAC2_A);
	for (i = 0; i < 3; i++) {
		priv->ndev->dev_addr[i * 2 + 1] = macAddress[i];
		priv->ndev->dev_addr[i * 2] = macAddress[i] >> 8;
	}
	RET(0);
}