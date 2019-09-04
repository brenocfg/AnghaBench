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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  spiObjectIdx0; } ;
typedef  int /*<<< orphan*/  Fd_t ;

/* Variables and functions */
 int /*<<< orphan*/  AssertCS () ; 
 int /*<<< orphan*/  DRV_SPI0_BufferAddWriteRead (unsigned char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DRV_SPI_Tasks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeassertCS () ; 
 int /*<<< orphan*/  SYS_PRINT (char*) ; 
 TYPE_1__ sysObj ; 

int spi_Write(Fd_t fd, unsigned char *pBuff, int len) {
  if (len > 512) {
    SYS_PRINT("BUFFER TOO SMALL");
    return 0;
  }

  AssertCS();
  uint8_t dummy[512];
  DRV_SPI0_BufferAddWriteRead(pBuff, dummy, len);
  DRV_SPI_Tasks(sysObj.spiObjectIdx0);
  DeassertCS();

  return len;
}