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
typedef  int /*<<< orphan*/  to_t ;

/* Variables and functions */
 int DATA_START_BLOCK ; 
 int FALSE ; 
 int /*<<< orphan*/  SD_CARD_ERROR_READ ; 
 int TRUE ; 
 int /*<<< orphan*/  m_error ; 
 int /*<<< orphan*/  m_spi_no ; 
 int m_status ; 
 int /*<<< orphan*/  platform_spi_blkread (int /*<<< orphan*/ ,size_t,void*) ; 
 int platform_spi_send_recv (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  platform_spi_transaction (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdcard_chipselect_high () ; 
 int /*<<< orphan*/  set_timeout (int /*<<< orphan*/ *,int) ; 
 scalar_t__ timed_out (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sdcard_read_data( uint8_t *dst, size_t count )
{
  to_t to;

  // wait for start block token
  set_timeout( &to, 100 * 1000 );
  while ((m_status = platform_spi_send_recv( m_spi_no, 8, 0xff)) == 0xff) {
    if (timed_out( &to )) {
      goto fail;
    }
  }

  if (m_status != DATA_START_BLOCK) {
    m_error = SD_CARD_ERROR_READ;
    goto fail;
  }
  // transfer data
  platform_spi_blkread( m_spi_no, count, (void *)dst );

  // discard crc
  platform_spi_transaction( m_spi_no, 16, 0xffff, 0, 0, 0, 0, 0 );

  sdcard_chipselect_high();
  return TRUE;

  fail:
  sdcard_chipselect_high();
  return FALSE;
}