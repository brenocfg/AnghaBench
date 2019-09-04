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
typedef  int /*<<< orphan*/  DRESULT ;
typedef  int BYTE ;

/* Variables and functions */
#define  CTRL_SYNC 129 
#define  CTRL_TRIM 128 
 int /*<<< orphan*/  RES_OK ; 
 int /*<<< orphan*/  RES_PARERR ; 

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
  switch (cmd) {
  case CTRL_TRIM:    /* no-op */
  case CTRL_SYNC:    /* no-op */
    return RES_OK;

  default:           /* anything else throws parameter error */
    return RES_PARERR;
  }
}