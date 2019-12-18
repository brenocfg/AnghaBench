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
 int /*<<< orphan*/  AT_HWCAP ; 
 unsigned long HWCAP_CRC32 ; 
 int /*<<< orphan*/  SSE42 (int) ; 
 int /*<<< orphan*/  crc32c ; 
 int /*<<< orphan*/  crc32c_hw ; 
 int /*<<< orphan*/  crc32c_hw_aarch64 ; 
 int /*<<< orphan*/  crc32c_sw ; 
 unsigned long getauxval (int /*<<< orphan*/ ) ; 

void crc32c_init(void) {
    #if defined(__X86_64__)||defined(__x86_64__)||defined(__ia64__)
    int sse42;
    SSE42(sse42);

    if (sse42) {
        crc32c = crc32c_hw;
    } else
    #endif
    /* Check if CRC instructions supported by aarch64 */
    #if defined(__linux__) && defined(__aarch64__) && defined(ARM_CRC32)
    unsigned long hwcap = getauxval(AT_HWCAP);

    if (hwcap & HWCAP_CRC32) {
        crc32c = crc32c_hw_aarch64;
    } else
    #endif
    {
        crc32c = crc32c_sw;
    }
}