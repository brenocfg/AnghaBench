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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int galois_double_mask32 (int) ; 
 int galois_double_mask64 (int) ; 

void galois_double(uint8_t* data, uint32_t len) {
    // FIXME - SIMD?

#ifdef _AMD64_
    while (len > sizeof(uint64_t)) {
        uint64_t v = *((uint64_t*)data), vv;

        vv = (v << 1) & 0xfefefefefefefefe;
        vv ^= galois_double_mask64(v) & 0x1d1d1d1d1d1d1d1d;
        *((uint64_t*)data) = vv;

        data += sizeof(uint64_t);
        len -= sizeof(uint64_t);
    }
#else
    while (len > sizeof(uint32_t)) {
        uint32_t v = *((uint32_t*)data), vv;

        vv = (v << 1) & 0xfefefefe;
        vv ^= galois_double_mask32(v) & 0x1d1d1d1d;
        *((uint32_t*)data) = vv;

        data += sizeof(uint32_t);
        len -= sizeof(uint32_t);
    }
#endif

    while (len > 0) {
        data[0] = (data[0] << 1) ^ ((data[0] & 0x80) ? 0x1d : 0);
        data++;
        len--;
    }
}