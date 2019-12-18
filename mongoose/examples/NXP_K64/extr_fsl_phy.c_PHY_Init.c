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
typedef  size_t uint32_t ;
typedef  scalar_t__ status_t ;
typedef  int /*<<< orphan*/  ENET_Type ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EnableClock (int /*<<< orphan*/ ) ; 
 size_t ENET_GetInstance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENET_SetSMI (int /*<<< orphan*/ *,size_t,int) ; 
 int PHY_100BASETX_FULLDUPLEX_MASK ; 
 int PHY_100BASETX_HALFDUPLEX_MASK ; 
 int PHY_10BASETX_FULLDUPLEX_MASK ; 
 int PHY_10BASETX_HALFDUPLEX_MASK ; 
 int /*<<< orphan*/  PHY_AUTONEG_ADVERTISE_REG ; 
 int /*<<< orphan*/  PHY_BASICCONTROL_REG ; 
 int /*<<< orphan*/  PHY_BASICSTATUS_REG ; 
 int PHY_BCTL_AUTONEG_MASK ; 
 int PHY_BCTL_RESET_MASK ; 
 int PHY_BCTL_RESTART_AUTONEG_MASK ; 
 size_t PHY_BSTATUS_AUTONEGCOMP_MASK ; 
 scalar_t__ PHY_Read (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,size_t*) ; 
 size_t PHY_TIMEOUT_COUNT ; 
 scalar_t__ PHY_Write (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kStatus_PHY_AutoNegotiateFail ; 
 scalar_t__ kStatus_Success ; 
 int /*<<< orphan*/ * s_enetClock ; 

status_t PHY_Init(ENET_Type *base, uint32_t phyAddr, uint32_t srcClock_Hz)
{
    uint32_t bssReg;
    uint32_t counter = PHY_TIMEOUT_COUNT;
    status_t result = kStatus_Success;
    uint32_t instance = ENET_GetInstance(base);

    /* Set SMI first. */
    CLOCK_EnableClock(s_enetClock[instance]);
    ENET_SetSMI(base, srcClock_Hz, false);

    /* Reset PHY. */
    result = PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result == kStatus_Success)
    {
        /* Set the negotiation. */
        result = PHY_Write(base, phyAddr, PHY_AUTONEG_ADVERTISE_REG,
                           (PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK |
                            PHY_10BASETX_FULLDUPLEX_MASK | PHY_10BASETX_HALFDUPLEX_MASK | 0x1U));
        if (result == kStatus_Success)
        {
            result = PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG,
                               (PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
            if (result == kStatus_Success)
            {
                /* Check auto negotiation complete. */
                while (counter --)
                {
                    result = PHY_Read(base, phyAddr, PHY_BASICSTATUS_REG, &bssReg);
                    if ( result == kStatus_Success)
                    {
                        if ((bssReg & PHY_BSTATUS_AUTONEGCOMP_MASK) != 0)
                        {
                            break;
                        } 
                    } 

                    if (!counter)
                    {
                        return kStatus_PHY_AutoNegotiateFail;
                    }
                }
            }
        }
    }

    return result;
}