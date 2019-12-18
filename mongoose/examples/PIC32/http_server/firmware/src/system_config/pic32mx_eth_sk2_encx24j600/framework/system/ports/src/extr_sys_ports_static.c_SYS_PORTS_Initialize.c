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

/* Variables and functions */
 int /*<<< orphan*/  PLIB_PORTS_AnPinsModeSelect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_PORTS_ChangeNoticeEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_PORTS_CnPinsEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_PORTS_CnPinsPullUpEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_PORTS_DirectionOutputSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLIB_PORTS_OpenDrainEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_PORTS_Write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORTS_ID_0 ; 
 int /*<<< orphan*/  PORTS_PIN_MODE_DIGITAL ; 
 int /*<<< orphan*/  PORT_CHANNEL_A ; 
 int /*<<< orphan*/  PORT_CHANNEL_B ; 
 int /*<<< orphan*/  SYS_PORT_AD1PCFG ; 
 int /*<<< orphan*/  SYS_PORT_A_LAT ; 
 int /*<<< orphan*/  SYS_PORT_A_ODC ; 
 int SYS_PORT_A_TRIS ; 
 int /*<<< orphan*/  SYS_PORT_B_LAT ; 
 int /*<<< orphan*/  SYS_PORT_B_ODC ; 
 int SYS_PORT_B_TRIS ; 
 int /*<<< orphan*/  SYS_PORT_CNEN ; 
 int /*<<< orphan*/  SYS_PORT_CNPUE ; 

void SYS_PORTS_Initialize(void)
{
    /* AN and CN Pins Initialization */
    PLIB_PORTS_AnPinsModeSelect(PORTS_ID_0, SYS_PORT_AD1PCFG, PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_CnPinsPullUpEnable(PORTS_ID_0, SYS_PORT_CNPUE);
    PLIB_PORTS_CnPinsEnable(PORTS_ID_0, SYS_PORT_CNEN);
    PLIB_PORTS_ChangeNoticeEnable(PORTS_ID_0);


    /* PORT A Initialization */
    PLIB_PORTS_OpenDrainEnable(PORTS_ID_0, PORT_CHANNEL_A, SYS_PORT_A_ODC);
    PLIB_PORTS_Write( PORTS_ID_0, PORT_CHANNEL_A,  SYS_PORT_A_LAT);
	PLIB_PORTS_DirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_A,  SYS_PORT_A_TRIS ^ 0xFFFF);

    /* PORT B Initialization */
    PLIB_PORTS_OpenDrainEnable(PORTS_ID_0, PORT_CHANNEL_B, SYS_PORT_B_ODC);
    PLIB_PORTS_Write( PORTS_ID_0, PORT_CHANNEL_B,  SYS_PORT_B_LAT);
	PLIB_PORTS_DirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_B,  SYS_PORT_B_TRIS ^ 0xFFFF);

}