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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACMD23 ; 
 int /*<<< orphan*/  CHECK_SSPIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD25 ; 
 int FALSE ; 
 int /*<<< orphan*/  SD_CARD_ERROR_ACMD23 ; 
 int /*<<< orphan*/  SD_CARD_ERROR_CMD25 ; 
 int /*<<< orphan*/  SD_CARD_ERROR_WRITE_MULTIPLE ; 
 scalar_t__ SD_CARD_TYPE_SDHC ; 
 int /*<<< orphan*/  WRITE_MULTIPLE_TOKEN ; 
 int /*<<< orphan*/  m_error ; 
 scalar_t__ m_type ; 
 scalar_t__ sdcard_acmd (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sdcard_chipselect_high () ; 
 int /*<<< orphan*/  sdcard_chipselect_low () ; 
 scalar_t__ sdcard_command (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdcard_wait_not_busy (int) ; 
 int /*<<< orphan*/  sdcard_write_data (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int sdcard_write_stop () ; 

int platform_sdcard_write_blocks( uint8_t ss_pin, uint32_t block, size_t num, const uint8_t *src )
{
  CHECK_SSPIN(ss_pin);

  if (sdcard_acmd( ACMD23, num )) {
    m_error = SD_CARD_ERROR_ACMD23;
    goto fail;
  }
  // generate byte address for pre-SDHC types
  if (m_type != SD_CARD_TYPE_SDHC) {
    block <<= 9;
  }
  if (sdcard_command( CMD25, block )) {
    m_error = SD_CARD_ERROR_CMD25;
    goto fail;
  }
  sdcard_chipselect_high();

  for (size_t b = 0; b < num; b++, src += 512) {
    sdcard_chipselect_low();

    // wait for previous write to finish
    if (! sdcard_wait_not_busy( 100 * 1000 )) {
      goto fail_write;
    }
    if (! sdcard_write_data( WRITE_MULTIPLE_TOKEN, src )) {
      goto fail_write;
    }

    sdcard_chipselect_high();
  }

  return sdcard_write_stop();

  fail_write:
  m_error = SD_CARD_ERROR_WRITE_MULTIPLE;
  fail:
  sdcard_chipselect_high();
  return FALSE;
}