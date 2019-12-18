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
typedef  int UINTEGER64 ;

/* Variables and functions */
 int UINT64 (int) ; 
 int openvpn_time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gen_timestamp(uint8_t *timestamp)
{
    /* Copies 8 bytes long timestamp into "timestamp" buffer.
     * Timestamp is Little-endian, 64-bit signed value representing the
     * number of tenths of a microsecond since January 1, 1601.
     */

    UINTEGER64 timestamp_ull;

    timestamp_ull = openvpn_time(NULL);
    timestamp_ull = (timestamp_ull + UINT64(11644473600)) * UINT64(10000000);

    /* store little endian value */
    timestamp[0] = timestamp_ull & UINT64(0xFF);
    timestamp[1] = (timestamp_ull  >> 8)  & UINT64(0xFF);
    timestamp[2] = (timestamp_ull  >> 16) & UINT64(0xFF);
    timestamp[3] = (timestamp_ull  >> 24) & UINT64(0xFF);
    timestamp[4] = (timestamp_ull  >> 32) & UINT64(0xFF);
    timestamp[5] = (timestamp_ull  >> 40) & UINT64(0xFF);
    timestamp[6] = (timestamp_ull  >> 48) & UINT64(0xFF);
    timestamp[7] = (timestamp_ull  >> 56) & UINT64(0xFF);
}