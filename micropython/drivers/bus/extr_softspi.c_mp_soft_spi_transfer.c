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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ delay_half; int polarity; scalar_t__ phase; int /*<<< orphan*/  sck; int /*<<< orphan*/  miso; int /*<<< orphan*/  mosi; } ;
typedef  TYPE_1__ mp_soft_spi_obj_t ;

/* Variables and functions */
 scalar_t__ MICROPY_HW_SOFTSPI_MIN_DELAY ; 
 int /*<<< orphan*/  mp_hal_delay_us_fast (scalar_t__) ; 
 int mp_hal_pin_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_hal_pin_write (int /*<<< orphan*/ ,int) ; 

void mp_soft_spi_transfer(void *self_in, size_t len, const uint8_t *src, uint8_t *dest) {
    mp_soft_spi_obj_t *self = (mp_soft_spi_obj_t*)self_in;
    uint32_t delay_half = self->delay_half;

    // only MSB transfer is implemented

    // If a port defines MICROPY_HW_SOFTSPI_MIN_DELAY, and the configured
    // delay_half is equal to this value, then the software SPI implementation
    // will run as fast as possible, limited only by CPU speed and GPIO time.
    #ifdef MICROPY_HW_SOFTSPI_MIN_DELAY
    if (delay_half == MICROPY_HW_SOFTSPI_MIN_DELAY) {
        for (size_t i = 0; i < len; ++i) {
            uint8_t data_out = src[i];
            uint8_t data_in = 0;
            for (int j = 0; j < 8; ++j, data_out <<= 1) {
                mp_hal_pin_write(self->mosi, (data_out >> 7) & 1);
                mp_hal_pin_write(self->sck, 1 - self->polarity);
                data_in = (data_in << 1) | mp_hal_pin_read(self->miso);
                mp_hal_pin_write(self->sck, self->polarity);
            }
            if (dest != NULL) {
                dest[i] = data_in;
            }
        }
        return;
    }
    #endif

    for (size_t i = 0; i < len; ++i) {
        uint8_t data_out = src[i];
        uint8_t data_in = 0;
        for (int j = 0; j < 8; ++j, data_out <<= 1) {
            mp_hal_pin_write(self->mosi, (data_out >> 7) & 1);
            if (self->phase == 0) {
                mp_hal_delay_us_fast(delay_half);
                mp_hal_pin_write(self->sck, 1 - self->polarity);
            } else {
                mp_hal_pin_write(self->sck, 1 - self->polarity);
                mp_hal_delay_us_fast(delay_half);
            }
            data_in = (data_in << 1) | mp_hal_pin_read(self->miso);
            if (self->phase == 0) {
                mp_hal_delay_us_fast(delay_half);
                mp_hal_pin_write(self->sck, self->polarity);
            } else {
                mp_hal_pin_write(self->sck, self->polarity);
                mp_hal_delay_us_fast(delay_half);
            }
        }
        if (dest != NULL) {
            dest[i] = data_in;
        }
    }
}