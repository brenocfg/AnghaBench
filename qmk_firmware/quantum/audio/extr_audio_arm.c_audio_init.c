#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dacsample_t ;
struct TYPE_2__ {int enable; int clicky_enable; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DACD1 ; 
 int /*<<< orphan*/  DACD2 ; 
 int /*<<< orphan*/  DAC_BUFFER_SIZE ; 
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  PAL_MODE_INPUT_ANALOG ; 
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CHANNEL_1 () ; 
 int /*<<< orphan*/  START_CHANNEL_2 () ; 
 TYPE_1__ audio_config ; 
 int audio_initialized ; 
 int /*<<< orphan*/  dac1cfg1 ; 
 int /*<<< orphan*/  dac1cfg2 ; 
 int /*<<< orphan*/  dacStart (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dacStartConversion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dac_buffer ; 
 scalar_t__ dac_buffer_2 ; 
 int /*<<< orphan*/  dacgrpcfg1 ; 
 int /*<<< orphan*/  dacgrpcfg2 ; 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  eeconfig_is_enabled () ; 
 int /*<<< orphan*/  eeconfig_read_audio () ; 
 int /*<<< orphan*/  palSetPadMode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  startup_song ; 
 int /*<<< orphan*/  stop_all_notes () ; 

void audio_init() {
    if (audio_initialized) {
        return;
    }

// Check EEPROM
#if defined(STM32_EEPROM_ENABLE) || defined(PROTOCOL_ARM_ATSAM) || defined(EEPROM_SIZE)
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    audio_config.raw = eeconfig_read_audio();
#else  // ARM EEPROM
    audio_config.enable        = true;
#    ifdef AUDIO_CLICKY_ON
    audio_config.clicky_enable = true;
#    endif
#endif  // ARM EEPROM

    /*
     * Starting DAC1 driver, setting up the output pin as analog as suggested
     * by the Reference Manual.
     */
    palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA, 5, PAL_MODE_INPUT_ANALOG);
    dacStart(&DACD1, &dac1cfg1);
    dacStart(&DACD2, &dac1cfg2);

    /*
     * Starting GPT6/7 driver, it is used for triggering the DAC.
     */
    START_CHANNEL_1();
    START_CHANNEL_2();

    /*
     * Starting a continuous conversion.
     */
    dacStartConversion(&DACD1, &dacgrpcfg1, (dacsample_t *)dac_buffer, DAC_BUFFER_SIZE);
    dacStartConversion(&DACD2, &dacgrpcfg2, (dacsample_t *)dac_buffer_2, DAC_BUFFER_SIZE);

    audio_initialized = true;

    if (audio_config.enable) {
        PLAY_SONG(startup_song);
    } else {
        stop_all_notes();
    }
}