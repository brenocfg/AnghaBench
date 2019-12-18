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
typedef  int uint32_t ;
typedef  scalar_t__ status_t ;
typedef  int /*<<< orphan*/  phy_speed_t ;
typedef  int /*<<< orphan*/  phy_duplex_t ;
typedef  int /*<<< orphan*/  ENET_Type ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_CONTROL1_REG ; 
 int PHY_CTL1_100FULLDUPLEX_MASK ; 
 int PHY_CTL1_100HALFDUPLEX_MASK ; 
 int PHY_CTL1_10FULLDUPLEX_MASK ; 
 int PHY_CTL1_SPEEDUPLX_MASK ; 
 scalar_t__ PHY_Read (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kPHY_FullDuplex ; 
 int /*<<< orphan*/  kPHY_HalfDuplex ; 
 int /*<<< orphan*/  kPHY_Speed100M ; 
 int /*<<< orphan*/  kPHY_Speed10M ; 
 scalar_t__ kStatus_Success ; 

status_t PHY_GetLinkSpeedDuplex(ENET_Type *base, uint32_t phyAddr, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(duplex);

    status_t result = kStatus_Success;
    uint32_t data, ctlReg;

    /* Read the control two register. */
    result = PHY_Read(base, phyAddr, PHY_CONTROL1_REG, &ctlReg);
    if (result == kStatus_Success)
    {
        data = ctlReg & PHY_CTL1_SPEEDUPLX_MASK;
        if ((PHY_CTL1_10FULLDUPLEX_MASK == data) || (PHY_CTL1_100FULLDUPLEX_MASK == data))
        {
            /* Full duplex. */
            *duplex = kPHY_FullDuplex;
        }
        else
        {
            /* Half duplex. */
            *duplex = kPHY_HalfDuplex;
        }

        data = ctlReg & PHY_CTL1_SPEEDUPLX_MASK;
        if ((PHY_CTL1_100HALFDUPLEX_MASK == data) || (PHY_CTL1_100FULLDUPLEX_MASK == data))
        {
            /* 100M speed. */
            *speed = kPHY_Speed100M;
        }
        else
        { /* 10M speed. */
            *speed = kPHY_Speed10M;
        }
    }

    return result;
}