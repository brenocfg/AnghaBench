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
 int /*<<< orphan*/  CMD12 ; 
 int /*<<< orphan*/  CMD18 ; 
 int FALSE ; 
 int /*<<< orphan*/  SD_CARD_ERROR_CMD12 ; 
 int /*<<< orphan*/  SD_CARD_ERROR_CMD18 ; 
 scalar_t__ SD_CARD_TYPE_SDHC ; 
 int TRUE ; 
 int /*<<< orphan*/  m_error ; 
 scalar_t__ m_type ; 
 int platform_sdcard_read_block (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdcard_chipselect_high () ; 
 int /*<<< orphan*/  sdcard_chipselect_low () ; 
 scalar_t__ sdcard_command (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sdcard_read_data (int /*<<< orphan*/ *,int) ; 

int platform_sdcard_read_blocks( uint8_t ss_pin, uint32_t block, size_t num, uint8_t *dst )
{
  CHECK_SSPIN(ss_pin);

  if (num == 0) {
    return TRUE;
  }
  if (num == 1) {
    return platform_sdcard_read_block( ss_pin, block, dst );
  }

  // generate byte address for pre-SDHC types
  if (m_type != SD_CARD_TYPE_SDHC) {
    block <<= 9;
  }

  // command READ_MULTIPLE_BLOCKS
  if (sdcard_command( CMD18, block )) {
    m_error = SD_CARD_ERROR_CMD18;
    goto fail;
  }

  // read required blocks
  while (num > 0) {
    sdcard_chipselect_low();
    if (sdcard_read_data( dst, 512 )) {
      num--;
      dst = &(dst[512]);
    } else {
      break;
    }
  }

  // issue command STOP_TRANSMISSION
  if (sdcard_command( CMD12, 0 )) {
    m_error = SD_CARD_ERROR_CMD12;
    goto fail;
  }
  sdcard_chipselect_high();
  return TRUE;

  fail:
  sdcard_chipselect_high();
  return FALSE;
}