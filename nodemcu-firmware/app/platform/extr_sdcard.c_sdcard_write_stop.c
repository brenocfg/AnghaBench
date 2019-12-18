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
 int FALSE ; 
 int /*<<< orphan*/  SD_CARD_ERROR_STOP_TRAN ; 
 int /*<<< orphan*/  STOP_TRAN_TOKEN ; 
 int TRUE ; 
 int /*<<< orphan*/  m_error ; 
 int /*<<< orphan*/  m_spi_no ; 
 int /*<<< orphan*/  platform_spi_transaction (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdcard_chipselect_high () ; 
 int /*<<< orphan*/  sdcard_chipselect_low () ; 
 int /*<<< orphan*/  sdcard_wait_not_busy (int) ; 

__attribute__((used)) static int sdcard_write_stop( void )
{
  sdcard_chipselect_low();

  if (! sdcard_wait_not_busy( 100 * 1000 )) {
    goto fail;
  }
  platform_spi_transaction( m_spi_no, 8, STOP_TRAN_TOKEN, 0, 0, 0, 0, 0 );
  if (! sdcard_wait_not_busy( 100 * 1000 )) {
    goto fail;
  }

  sdcard_chipselect_high();
  return TRUE;

  fail:
  m_error = SD_CARD_ERROR_STOP_TRAN;
  sdcard_chipselect_high();
  return FALSE;
}