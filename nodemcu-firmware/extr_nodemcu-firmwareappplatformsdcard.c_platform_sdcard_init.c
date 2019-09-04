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
typedef  int /*<<< orphan*/  to_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACMD41 ; 
 int /*<<< orphan*/  CHECK_SSPIN (int) ; 
 int /*<<< orphan*/  CMD0 ; 
 int /*<<< orphan*/  CMD58 ; 
 int /*<<< orphan*/  CMD8 ; 
 int FALSE ; 
 int /*<<< orphan*/  PLATFORM_GPIO_FLOAT ; 
 int /*<<< orphan*/  PLATFORM_GPIO_HIGH ; 
 int /*<<< orphan*/  PLATFORM_GPIO_OUTPUT ; 
 int R1_IDLE_STATE ; 
 int R1_ILLEGAL_COMMAND ; 
 scalar_t__ R1_READY_STATE ; 
 scalar_t__ SD_CARD_ERROR_CMD58 ; 
 scalar_t__ SD_CARD_TYPE_INVALID ; 
 scalar_t__ SD_CARD_TYPE_SD1 ; 
 scalar_t__ SD_CARD_TYPE_SD2 ; 
 scalar_t__ SD_CARD_TYPE_SDHC ; 
 int TRUE ; 
 scalar_t__ m_error ; 
 int m_spi_no ; 
 int /*<<< orphan*/  m_ss_pin ; 
 int m_status ; 
 scalar_t__ m_type ; 
 int /*<<< orphan*/  platform_gpio_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_gpio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_spi_send_recv (int,int,int) ; 
 int /*<<< orphan*/  platform_spi_transaction (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sdcard_acmd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdcard_chipselect_high () ; 
 int sdcard_command (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_timeout (int /*<<< orphan*/ *,int) ; 
 int spi_set_clkdiv (int,int) ; 
 scalar_t__ timed_out (int /*<<< orphan*/ *) ; 

int platform_sdcard_init( uint8_t spi_no, uint8_t ss_pin )
{
  uint32_t arg, user_spi_clkdiv;
  to_t to;

  m_type = SD_CARD_TYPE_INVALID;
  m_error = 0;

  if (spi_no > 1) {
    return FALSE;
  }
  m_spi_no = spi_no;
  CHECK_SSPIN(ss_pin);

  platform_gpio_write( m_ss_pin, PLATFORM_GPIO_HIGH );
  platform_gpio_mode( m_ss_pin, PLATFORM_GPIO_OUTPUT, PLATFORM_GPIO_FLOAT );

  // set SPI clock to 400 kHz for init phase
  user_spi_clkdiv = spi_set_clkdiv( m_spi_no, 200 );

  // apply initialization sequence:
  // keep ss and io high, apply clock for max(1ms; 74cc)
  // 1ms requires 400cc @ 400kHz
  for (int i = 0; i < 2; i++) {
    platform_spi_transaction( m_spi_no, 0, 0, 0, 0, 0, 200, 0 );
  }

  // command to go idle in SPI mode
  set_timeout( &to, 500 * 1000 );
  while (sdcard_command( CMD0, 0 ) != R1_IDLE_STATE) {
    if (timed_out( &to )) {
      goto fail;
    }
  }

  set_timeout( &to, 500 * 1000 );
  while (1) {
    if (sdcard_command( CMD8, 0x1aa) == (R1_ILLEGAL_COMMAND | R1_IDLE_STATE)) {
      m_type = SD_CARD_TYPE_SD1;
      break;
    }
    for (uint8_t i = 0; i < 4; i++) {
      m_status = platform_spi_send_recv( m_spi_no, 8, 0xff );
    }
    if (m_status == 0xaa) {
      m_type = SD_CARD_TYPE_SD2;
      break;
    }
    if (timed_out( &to )) {
      goto fail;
    }
  }
  // initialize card and send host supports SDHC if SD2
  arg = m_type == SD_CARD_TYPE_SD2 ? 0x40000000 : 0;

  set_timeout( &to, 500 * 1000 );
  while (sdcard_acmd( ACMD41, arg ) != R1_READY_STATE) {
    if (timed_out( &to )) {
      goto fail;
    }
  }
  // if SD2 read OCR register to check for SDHC card
  if (m_type == SD_CARD_TYPE_SD2) {
    if (sdcard_command( CMD58, 0 )) {
      m_error = SD_CARD_ERROR_CMD58;
      goto fail;
    }
    if ((platform_spi_send_recv( m_spi_no, 8, 0xff ) & 0xC0) == 0xC0) {
      m_type = SD_CARD_TYPE_SDHC;
    }
    // Discard rest of ocr - contains allowed voltage range.
    for (uint8_t i = 0; i < 3; i++) {
      platform_spi_send_recv( m_spi_no, 8, 0xff);
    }
  }
  sdcard_chipselect_high();

  // re-apply user's spi clock divider
  spi_set_clkdiv( m_spi_no, user_spi_clkdiv );

  return TRUE;

  fail:
  sdcard_chipselect_high();
  return FALSE;
}