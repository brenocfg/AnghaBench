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
 int PLIB_SPI_TransmitBufferIsFull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_ID_1 ; 

bool DRV_SPI0_TransmitterBufferIsFull(void)
{
    return (PLIB_SPI_TransmitBufferIsFull(SPI_ID_1));
}