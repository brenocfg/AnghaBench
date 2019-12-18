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
 int /*<<< orphan*/  INT_ID_0 ; 
 int /*<<< orphan*/  INT_PRIORITY_LEVEL2 ; 
 int /*<<< orphan*/  INT_SOURCE_CHANGE_NOTICE ; 
 int /*<<< orphan*/  INT_SUBPRIORITY_LEVEL0 ; 
 int /*<<< orphan*/  INT_VECTOR_CN ; 
 int /*<<< orphan*/  PLIB_INT_SourceEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_INT_SourceFlagClear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_INT_VectorPrioritySet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_INT_VectorSubPrioritySet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_PORTS_AnPinsModeSelect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_PORTS_ChangeNoticeEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_PORTS_CnPinsEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_PORTS_CnPinsPullUpEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_PORTS_DirectionOutputSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLIB_PORTS_OpenDrainEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_PORTS_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_PORTS_Write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORTS_ID_0 ; 
 int /*<<< orphan*/  PORTS_PIN_MODE_DIGITAL ; 
 int /*<<< orphan*/  PORT_CHANNEL_D ; 
 int /*<<< orphan*/  SYS_PORT_AD1PCFG ; 
 int /*<<< orphan*/  SYS_PORT_CNEN ; 
 int /*<<< orphan*/  SYS_PORT_CNPUE ; 
 int /*<<< orphan*/  SYS_PORT_D_LAT ; 
 int /*<<< orphan*/  SYS_PORT_D_ODC ; 
 int SYS_PORT_D_TRIS ; 

void SYS_PORTS_Initialize(void)
{
    /* AN and CN Pins Initialization */
    PLIB_PORTS_AnPinsModeSelect(PORTS_ID_0, SYS_PORT_AD1PCFG, PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_CnPinsPullUpEnable(PORTS_ID_0, SYS_PORT_CNPUE);
    PLIB_PORTS_CnPinsEnable(PORTS_ID_0, SYS_PORT_CNEN);
    PLIB_PORTS_ChangeNoticeEnable(PORTS_ID_0);

    PLIB_PORTS_Read(PORTS_ID_0, PORT_CHANNEL_D);    
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_CHANGE_NOTICE);         
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_CHANGE_NOTICE);
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_CN, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_CN, INT_SUBPRIORITY_LEVEL0);          
    
    
    /* PORT D Initialization */
    PLIB_PORTS_OpenDrainEnable(PORTS_ID_0, PORT_CHANNEL_D, SYS_PORT_D_ODC);
    PLIB_PORTS_Write( PORTS_ID_0, PORT_CHANNEL_D,  SYS_PORT_D_LAT);
	PLIB_PORTS_DirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_D,  SYS_PORT_D_TRIS ^ 0xFFFF);
    
}