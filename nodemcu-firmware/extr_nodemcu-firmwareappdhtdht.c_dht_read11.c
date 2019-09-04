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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DHTLIB_DHT11_WAKEUP ; 
 int DHTLIB_ERROR_CHECKSUM ; 
 void* DHTLIB_INVALID_VALUE ; 
 int DHTLIB_OK ; 
 scalar_t__* dht_bytes ; 
 void* dht_humidity ; 
 int dht_readSensor (scalar_t__,int /*<<< orphan*/ ) ; 
 void* dht_temperature ; 

int dht_read11(uint8_t pin)
{
    // READ VALUES
    int rv = dht_readSensor(pin, DHTLIB_DHT11_WAKEUP);
    if (rv != DHTLIB_OK)
    {
        dht_humidity    = DHTLIB_INVALID_VALUE; // invalid value, or is NaN prefered?
        dht_temperature = DHTLIB_INVALID_VALUE; // invalid value
        return rv;
    }

    // CONVERT AND STORE
    dht_humidity    = dht_bytes[0];  // dht_bytes[1] == 0;
    dht_temperature = dht_bytes[2];  // dht_bytes[3] == 0;

    // TEST CHECKSUM
    // dht_bytes[1] && dht_bytes[3] both 0
    uint8_t sum = dht_bytes[0] + dht_bytes[1] + dht_bytes[2] + dht_bytes[3];
    if (dht_bytes[4] != sum) return DHTLIB_ERROR_CHECKSUM;

    return DHTLIB_OK;
}