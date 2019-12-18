#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct TYPE_12__ {int tick; } ;
struct TYPE_11__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
struct TYPE_8__ {int /*<<< orphan*/ * b; int /*<<< orphan*/ * g; int /*<<< orphan*/ * r; } ;
struct TYPE_10__ {TYPE_2__ rgb; } ;
struct TYPE_7__ {int /*<<< orphan*/  SDB_N; } ;
struct TYPE_9__ {TYPE_1__ bit; } ;

/* Variables and functions */
 double BREATHE_MAX_STEP ; 
 double BREATHE_MIN_STEP ; 
 double BREATHE_STEP ; 
 int /*<<< orphan*/  I2C_LED_Q_GCR (size_t) ; 
 int /*<<< orphan*/  I2C_LED_Q_PWM (size_t) ; 
 size_t ISSI3733_DRIVER_COUNT ; 
 size_t ISSI3733_LED_COUNT ; 
 double breathe_dir ; 
 int breathe_mult ; 
 TYPE_6__ g_rgb_counters ; 
 scalar_t__ gcr_actual ; 
 scalar_t__ gcr_actual_last ; 
 int /*<<< orphan*/  i2c_led_q_run () ; 
 scalar_t__ i2c_led_q_running ; 
 double led_animation_breathe_cur ; 
 scalar_t__ led_animation_breathing ; 
 float led_animation_speed ; 
 TYPE_5__* led_buffer ; 
 int /*<<< orphan*/  led_enabled ; 
 TYPE_4__* led_map ; 
 float pomod ; 
 TYPE_3__ sr_exp_data ; 

void flush(void) {
#ifdef USE_MASSDROP_CONFIGURATOR
    if (!led_enabled) {
        return;
    }  // Prevent calculations and I2C traffic if LED drivers are not enabled
#else
    if (!sr_exp_data.bit.SDB_N) {
        return;
    }  // Prevent calculations and I2C traffic if LED drivers are not enabled
#endif

    // Wait for previous transfer to complete
    while (i2c_led_q_running) {
    }

    // Copy buffer to live DMA region
    for (uint8_t i = 0; i < ISSI3733_LED_COUNT; i++) {
        *led_map[i].rgb.r = led_buffer[i].r;
        *led_map[i].rgb.g = led_buffer[i].g;
        *led_map[i].rgb.b = led_buffer[i].b;
    }

#ifdef USE_MASSDROP_CONFIGURATOR
    breathe_mult = 1;

    if (led_animation_breathing) {
        //+60us 119 LED
        led_animation_breathe_cur += BREATHE_STEP * breathe_dir;

        if (led_animation_breathe_cur >= BREATHE_MAX_STEP)
            breathe_dir = -1;
        else if (led_animation_breathe_cur <= BREATHE_MIN_STEP)
            breathe_dir = 1;

        // Brightness curve created for 256 steps, 0 - ~98%
        breathe_mult = 0.000015 * led_animation_breathe_cur * led_animation_breathe_cur;
        if (breathe_mult > 1)
            breathe_mult = 1;
        else if (breathe_mult < 0)
            breathe_mult = 0;
    }

    // This should only be performed once per frame
    pomod = (float)((g_rgb_counters.tick / 10) % (uint32_t)(1000.0f / led_animation_speed)) / 10.0f * led_animation_speed;
    pomod *= 100.0f;
    pomod = (uint32_t)pomod % 10000;
    pomod /= 100.0f;

#endif  // USE_MASSDROP_CONFIGURATOR

    uint8_t drvid;

    // NOTE: GCR does not need to be timed with LED processing, but there is really no harm
    if (gcr_actual != gcr_actual_last) {
        for (drvid = 0; drvid < ISSI3733_DRIVER_COUNT; drvid++) I2C_LED_Q_GCR(drvid);  // Queue data
        gcr_actual_last = gcr_actual;
    }

    for (drvid = 0; drvid < ISSI3733_DRIVER_COUNT; drvid++) I2C_LED_Q_PWM(drvid);  // Queue data

    i2c_led_q_run();
}