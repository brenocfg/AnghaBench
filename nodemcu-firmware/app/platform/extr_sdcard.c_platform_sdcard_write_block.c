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
 int /*<<< orphan*/  CHECK_SSPIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD24 ; 
 int /*<<< orphan*/  DATA_START_BLOCK ; 
 int FALSE ; 
 int /*<<< orphan*/  SD_CARD_ERROR_CMD24 ; 
 scalar_t__ SD_CARD_TYPE_SDHC ; 
 int TRUE ; 
 int /*<<< orphan*/  m_error ; 
 scalar_t__ m_type ; 
 int /*<<< orphan*/  sdcard_chipselect_high () ; 
 scalar_t__ sdcard_command (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdcard_write_data (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int platform_sdcard_write_block( uint8_t ss_pin, uint32_t block, const uint8_t *src )
{
  CHECK_SSPIN(ss_pin);

  // generate byte address for pre-SDHC types
  if (m_type != SD_CARD_TYPE_SDHC) {
    block <<= 9;
  }
  if (sdcard_command( CMD24, block )) {
    m_error = SD_CARD_ERROR_CMD24;
    goto fail;
  }
  if (! sdcard_write_data( DATA_START_BLOCK, src )) {
    goto fail;
  }

  sdcard_chipselect_high();
  return TRUE;

  fail:
  sdcard_chipselect_high();
  return FALSE;
}