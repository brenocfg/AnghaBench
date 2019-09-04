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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vnt_private {unsigned short wBeaconInterval; scalar_t__ PortOffset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARDbGetCurrentTSF (struct vnt_private*,int*) ; 
 int CARDqGetNextTBTT (int,unsigned short) ; 
 scalar_t__ MAC_REG_BI ; 
 scalar_t__ MAC_REG_NEXTTBTT ; 
 int /*<<< orphan*/  MAC_REG_TFTCTL ; 
 int /*<<< orphan*/  MACvRegBitsOn (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TFTCTL_TBTTSYNCEN ; 
 int /*<<< orphan*/  VNSvOutPortD (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VNSvOutPortW (scalar_t__,unsigned short) ; 

bool CARDbSetBeaconPeriod(struct vnt_private *priv,
			  unsigned short wBeaconInterval)
{
	u64 qwNextTBTT = 0;

	CARDbGetCurrentTSF(priv, &qwNextTBTT); /* Get Local TSF counter */

	qwNextTBTT = CARDqGetNextTBTT(qwNextTBTT, wBeaconInterval);

	/* set HW beacon interval */
	VNSvOutPortW(priv->PortOffset + MAC_REG_BI, wBeaconInterval);
	priv->wBeaconInterval = wBeaconInterval;
	/* Set NextTBTT */
	VNSvOutPortD(priv->PortOffset + MAC_REG_NEXTTBTT, (u32)qwNextTBTT);
	VNSvOutPortD(priv->PortOffset + MAC_REG_NEXTTBTT + 4,
		     (u32)(qwNextTBTT >> 32));
	MACvRegBitsOn(priv->PortOffset, MAC_REG_TFTCTL, TFTCTL_TBTTSYNCEN);

	return true;
}