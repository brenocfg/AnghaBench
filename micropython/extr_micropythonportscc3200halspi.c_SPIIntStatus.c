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
typedef  scalar_t__ tBoolean ;

/* Variables and functions */
 scalar_t__ APPS_CONFIG_BASE ; 
 scalar_t__ APPS_CONFIG_O_DMA_DONE_INT_STS_MASKED ; 
 scalar_t__ APPS_CONFIG_O_DMA_DONE_INT_STS_RAW ; 
 unsigned long HWREG (scalar_t__) ; 
 scalar_t__ MCSPI_O_IRQENABLE ; 
 scalar_t__ MCSPI_O_IRQSTATUS ; 
 unsigned long SPIDmaMaskGet (unsigned long) ; 
 unsigned long SPI_INT_DMARX ; 
 unsigned long SPI_INT_DMATX ; 

unsigned long
SPIIntStatus(unsigned long ulBase, tBoolean bMasked)
{
  unsigned long ulIntStat;
  unsigned long ulIntFlag;
  unsigned long ulDmaMsk;

  //
  // Get SPI interrupt status
  //
  ulIntFlag = HWREG(ulBase + MCSPI_O_IRQSTATUS) & 0x0003000F;

  if(bMasked)
  {
     ulIntFlag &= HWREG(ulBase + MCSPI_O_IRQENABLE);
  }

  //
  // Get the interrupt bit
  //
  ulDmaMsk = SPIDmaMaskGet(ulBase);

  //
  // Get the DMA interrupt status
  //
  if(bMasked)
  {
    ulIntStat = HWREG(APPS_CONFIG_BASE + APPS_CONFIG_O_DMA_DONE_INT_STS_MASKED);
  }
  else
  {
    ulIntStat = HWREG(APPS_CONFIG_BASE + APPS_CONFIG_O_DMA_DONE_INT_STS_RAW);
  }

  //
  // Get SPI Tx DMA done status
  //
  if(ulIntStat & ulDmaMsk)
  {
     ulIntFlag |= SPI_INT_DMATX;
  }

  //
  // Get SPI Rx DMA done status
  //
  if(ulIntStat & (ulDmaMsk >> 1))
  {
     ulIntFlag |= SPI_INT_DMARX;
  }

  //
  // Return status
  //
  return(ulIntFlag);
}