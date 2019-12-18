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
typedef  int /*<<< orphan*/  DSTATUS ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  STA_NOINIT ; 
 int /*<<< orphan*/  m_status ; 
 scalar_t__ platform_sdcard_init (int,int /*<<< orphan*/ ) ; 

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
  int result;

  if (platform_sdcard_init( 1, pdrv )) {
    m_status &= ~STA_NOINIT;
  }

  return m_status;
}