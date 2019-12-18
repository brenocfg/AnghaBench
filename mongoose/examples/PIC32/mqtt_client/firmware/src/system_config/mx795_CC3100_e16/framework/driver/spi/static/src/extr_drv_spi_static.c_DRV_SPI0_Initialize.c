#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int maxElements; int reserveElements; } ;
struct TYPE_5__ {int numTrfsSmPolled; int /*<<< orphan*/ * operationEnded; int /*<<< orphan*/ * operationStarting; int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  SYS_MODULE_OBJ ;
typedef  TYPE_1__ DRV_SPI_OBJ ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_BUS_PERIPHERAL_2 ; 
 int /*<<< orphan*/  DRV_SPI_INDEX_0 ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_CreateQueue (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_SUCCESS ; 
 int /*<<< orphan*/  PLIB_SPI_AudioProtocolDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_BaudRateSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLIB_SPI_BufferClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_ClockPolaritySelect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_CommunicationWidthSelect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_Enable (int /*<<< orphan*/ ) ; 
 scalar_t__ PLIB_SPI_ExistsAudioProtocolControl (int /*<<< orphan*/ ) ; 
 scalar_t__ PLIB_SPI_ExistsFIFOControl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_FIFODisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_FramedCommunicationDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_InputSamplePhaseSelect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_MasterEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_OutputDataPhaseSelect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_PinDisable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_ReceiverOverflowClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_StopInIdleEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_CLOCK_POLARITY_IDLE_LOW ; 
 int /*<<< orphan*/  SPI_COMMUNICATION_WIDTH_8BITS ; 
 int /*<<< orphan*/  SPI_ID_1 ; 
 int /*<<< orphan*/  SPI_INPUT_SAMPLING_PHASE_IN_MIDDLE ; 
 int /*<<< orphan*/  SPI_OUTPUT_DATA_PHASE_ON_IDLE_TO_ACTIVE_CLOCK ; 
 int /*<<< orphan*/  SPI_PIN_SLAVE_SELECT ; 
 int /*<<< orphan*/  SYS_ASSERT (int,char*) ; 
 int /*<<< orphan*/  SYS_CLK_PeripheralFrequencyGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_MODULE_OBJ_INVALID ; 
 TYPE_1__ gDrvSPI0Obj ; 
 int /*<<< orphan*/  hQueueManager ; 
 TYPE_2__ qInitData ; 
 int /*<<< orphan*/  qmInitData ; 

SYS_MODULE_OBJ DRV_SPI0_Initialize(void)
{
    DRV_SPI_OBJ *dObj = (DRV_SPI_OBJ*)NULL;

    dObj = &gDrvSPI0Obj;

    /* Disable the SPI module to configure it*/
    PLIB_SPI_Disable ( SPI_ID_1 );

    /* Set up Master or Slave Mode*/
    PLIB_SPI_MasterEnable ( SPI_ID_1 );
    PLIB_SPI_PinDisable(SPI_ID_1, SPI_PIN_SLAVE_SELECT);

    /* Set up if the SPI is allowed to run while the rest of the CPU is in idle mode*/
    PLIB_SPI_StopInIdleEnable( SPI_ID_1 );

    /* Set up clock Polarity and output data phase*/
    PLIB_SPI_ClockPolaritySelect( SPI_ID_1, SPI_CLOCK_POLARITY_IDLE_LOW );
    PLIB_SPI_OutputDataPhaseSelect( SPI_ID_1, SPI_OUTPUT_DATA_PHASE_ON_IDLE_TO_ACTIVE_CLOCK );

    /* Set up the Input Sample Phase*/
    PLIB_SPI_InputSamplePhaseSelect ( SPI_ID_1, SPI_INPUT_SAMPLING_PHASE_IN_MIDDLE);

    /* Communication Width Selection */
    PLIB_SPI_CommunicationWidthSelect ( SPI_ID_1, SPI_COMMUNICATION_WIDTH_8BITS );

    /* Baud rate selection */
    PLIB_SPI_BaudRateSet( SPI_ID_1 , SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_2), 10000000 );

    /* Protocol selection */
    PLIB_SPI_FramedCommunicationDisable( SPI_ID_1  );
    #if defined (PLIB_SPI_ExistsAudioProtocolControl)
            if (PLIB_SPI_ExistsAudioProtocolControl(SPI_ID_1))
            {
                PLIB_SPI_AudioProtocolDisable(SPI_ID_1);
            }
    #endif

    /* Buffer type selection */
    #if defined (PLIB_SPI_ExistsFIFOControl)
        if (PLIB_SPI_ExistsFIFOControl( SPI_ID_1 ))
        {
            PLIB_SPI_FIFODisable( SPI_ID_1 );
        }
    #endif

    PLIB_SPI_BufferClear( SPI_ID_1 );
    PLIB_SPI_ReceiverOverflowClear ( SPI_ID_1 );

    /* Initialize Queue only once for all instances of SPI driver*/
    if (DRV_SPI_SYS_QUEUE_Initialize(&qmInitData, &hQueueManager) != DRV_SPI_SYS_QUEUE_SUCCESS)
    {
        SYS_ASSERT(false, "\r\nSPI Driver: Could not create queuing system.");
        return SYS_MODULE_OBJ_INVALID;
    }

    /* Update the Queue parameters. */
    qInitData.maxElements = 10; //Queue size
    qInitData.reserveElements = 1; //Mininmum number of job queues reserved

    /* Create Queue for this instance of SPI */
    if (DRV_SPI_SYS_QUEUE_CreateQueue(hQueueManager, &qInitData, &dObj->queue) != DRV_SPI_SYS_QUEUE_SUCCESS)
    {
        SYS_ASSERT(false, "\r\nSPI Driver: Could not set up driver instance queue.");
        return SYS_MODULE_OBJ_INVALID;

    }

    /* Update the SPI OBJECT parameters. */
    dObj->operationStarting = NULL;
    dObj->operationEnded = NULL;
    dObj->numTrfsSmPolled = 16;

    /* Enable the Module */
    PLIB_SPI_Enable(SPI_ID_1);

    return (SYS_MODULE_OBJ)DRV_SPI_INDEX_0 ;
}