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

/* Variables and functions */

inline void SetSDR1( int sdr ) {
#if 0
    int i,j;
#endif
    __asm__("mtsdr1 3");
#if 0
    __asm__("sync");
    __asm__("isync");
    __asm__("ptesync");

    for( i = 0; i < 256; i++ ) {
    j = i << 12;
    __asm__("tlbie %0,0" : : "r" (j));
    }
    __asm__("eieio");
    __asm__("tlbsync");
    __asm__("ptesync");
#endif
}