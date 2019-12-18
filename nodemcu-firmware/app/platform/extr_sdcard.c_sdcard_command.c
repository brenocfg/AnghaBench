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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int CMD0 ; 
 int CMD12 ; 
 int /*<<< orphan*/  m_spi_no ; 
 int m_status ; 
 int platform_spi_send_recv (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  platform_spi_transaction (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdcard_chipselect_low () ; 
 int /*<<< orphan*/  sdcard_wait_not_busy (int) ; 

__attribute__((used)) static uint8_t sdcard_command( uint8_t cmd, uint32_t arg )
{
  sdcard_chipselect_low();

  // wait until card is busy
  sdcard_wait_not_busy( 100 * 1000 );

  // send command
  // with precalculated CRC - correct for CMD0 with arg zero or CMD8 with arg 0x1AA
  const uint8_t crc = cmd == CMD0 ? 0x95 : 0x87;
  platform_spi_transaction( m_spi_no, 16, (cmd | 0x40) << 8 | arg >> 24, 32, arg << 8 | crc, 0, 0, 0 );

  // skip dangling byte of data transfer
  if (cmd == CMD12) {
    platform_spi_transaction( m_spi_no, 8, 0xff, 0, 0, 0, 0, 0 );
  }

  // wait for response
  for (uint8_t i = 0; ((m_status = platform_spi_send_recv( m_spi_no, 8, 0xff )) & 0x80) && i != 0xFF; i++) ;

  return m_status;
}