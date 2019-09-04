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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int DHTLIB_ERROR_TIMEOUT ; 
 int DHTLIB_OK ; 
 scalar_t__ DHTLIB_TIMEOUT ; 
 int /*<<< orphan*/  DIRECT_MODE_INPUT (int) ; 
 int /*<<< orphan*/  DIRECT_MODE_OUTPUT (int) ; 
 scalar_t__ DIRECT_READ (int) ; 
 int /*<<< orphan*/  DIRECT_WRITE_HIGH (int) ; 
 int /*<<< orphan*/  DIRECT_WRITE_LOW (int) ; 
 scalar_t__ LOW ; 
 int /*<<< orphan*/  PLATFORM_GPIO_OUTPUT ; 
 int /*<<< orphan*/  PLATFORM_GPIO_PULLUP ; 
 int* dht_bytes ; 
 int /*<<< orphan*/  ets_intr_lock () ; 
 int /*<<< orphan*/  ets_intr_unlock () ; 
 int /*<<< orphan*/  os_delay_us (int) ; 
 int /*<<< orphan*/  platform_gpio_mode (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int system_get_time () ; 

int dht_readSensor(uint8_t pin, uint8_t wakeupDelay)
{
    // INIT BUFFERVAR TO RECEIVE DATA
    uint8_t mask = 128;
    uint8_t idx = 0;
    uint8_t i = 0;

    // replace digitalRead() with Direct Port Reads.
    // reduces footprint ~100 bytes => portability issue?
    // direct port read is about 3x faster
    // uint8_t bit = digitalPinToBitMask(pin);
    // uint8_t port = digitalPinToPort(pin);
    // volatile uint8_t *PIR = portInputRegister(port);

    // EMPTY BUFFER
    for (i = 0; i < 5; i++) dht_bytes[i] = 0;

    // REQUEST SAMPLE
    // pinMode(pin, OUTPUT);
    platform_gpio_mode(pin, PLATFORM_GPIO_OUTPUT, PLATFORM_GPIO_PULLUP);
    DIRECT_MODE_OUTPUT(pin);
    // digitalWrite(pin, LOW); // T-be
    DIRECT_WRITE_LOW(pin);
    // delay(wakeupDelay);
    for (i = 0; i < wakeupDelay; i++) os_delay_us(1000);
    // Disable interrupts
    ets_intr_lock();
    // digitalWrite(pin, HIGH);   // T-go
    DIRECT_WRITE_HIGH(pin);
    os_delay_us(40);
    // pinMode(pin, INPUT);
    DIRECT_MODE_INPUT(pin);

    // GET ACKNOWLEDGE or TIMEOUT
    uint16_t loopCntLOW = DHTLIB_TIMEOUT;
    while (DIRECT_READ(pin) == LOW )  // T-rel
    {
        os_delay_us(1);
        if (--loopCntLOW == 0) return DHTLIB_ERROR_TIMEOUT;
    }

    uint16_t loopCntHIGH = DHTLIB_TIMEOUT;
    while (DIRECT_READ(pin) != LOW )  // T-reh
    {
        os_delay_us(1);
        if (--loopCntHIGH == 0) return DHTLIB_ERROR_TIMEOUT;
    }

    // READ THE OUTPUT - 40 BITS => 5 BYTES
    for (i = 40; i != 0; i--)
    {
        loopCntLOW = DHTLIB_TIMEOUT;
        while (DIRECT_READ(pin) == LOW )
        {
            os_delay_us(1);
            if (--loopCntLOW == 0) return DHTLIB_ERROR_TIMEOUT;
        }

        uint32_t t = system_get_time();

        loopCntHIGH = DHTLIB_TIMEOUT;
        while (DIRECT_READ(pin) != LOW )
        {
            os_delay_us(1);
            if (--loopCntHIGH == 0) return DHTLIB_ERROR_TIMEOUT;
        }

        if ((system_get_time() - t) > 40)
        {
            dht_bytes[idx] |= mask;
        }
        mask >>= 1;
        if (mask == 0)   // next byte?
        {
            mask = 128;
            idx++;
        }
    }
    // Enable interrupts
    ets_intr_unlock();
    // pinMode(pin, OUTPUT);
    DIRECT_MODE_OUTPUT(pin);
    // digitalWrite(pin, HIGH);
    DIRECT_WRITE_HIGH(pin);

    return DHTLIB_OK;
}