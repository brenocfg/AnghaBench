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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  size_t int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PLIB_SPI_BufferRead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_BufferWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_ReceiverBufferIsFull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_TransmitBufferIsFull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_ID_1 ; 

int32_t DRV_SPI0_BufferAddWriteRead(const void * txBuffer, void * rxBuffer, uint32_t size)
{
    bool continueLoop;
    int32_t txcounter = 0;
    int32_t rxcounter = 0;
    do {
        continueLoop = false;
        if(!PLIB_SPI_TransmitBufferIsFull(SPI_ID_1) && txcounter < size)
        {
            PLIB_SPI_BufferWrite(SPI_ID_1, ((uint8_t*)txBuffer)[txcounter]);
            txcounter++;
            continueLoop = true;
        }

        while (txcounter != rxcounter)
        {
            while(!PLIB_SPI_ReceiverBufferIsFull(SPI_ID_1));
            ((uint8_t*)rxBuffer)[rxcounter] = PLIB_SPI_BufferRead(SPI_ID_1);
            rxcounter++;
            continueLoop = true;
        }
        if (txcounter > rxcounter)
        {
            continueLoop = true;
        }
    }while(continueLoop);
    return txcounter;
}