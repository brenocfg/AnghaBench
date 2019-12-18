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

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SD_CARD_ERROR_READ_REG ; 
 int /*<<< orphan*/  m_error ; 
 int /*<<< orphan*/  sdcard_chipselect_high () ; 
 scalar_t__ sdcard_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sdcard_read_data (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sdcard_read_register( uint8_t cmd, uint8_t *buf )
{
  if (sdcard_command( cmd, 0 )) {
    m_error = SD_CARD_ERROR_READ_REG;
    goto fail;
  }
  return sdcard_read_data( buf, 16 );

  fail:
  sdcard_chipselect_high();
  return FALSE;
}