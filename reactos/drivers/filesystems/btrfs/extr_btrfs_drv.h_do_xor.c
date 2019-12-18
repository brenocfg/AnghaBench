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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  __m128i ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_load_si128 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _mm_store_si128 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_xor_si128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ have_sse2 ; 

__attribute__((used)) static __inline void do_xor(uint8_t* buf1, uint8_t* buf2, uint32_t len) {
    uint32_t j;
#ifndef __REACTOS__
    __m128i x1, x2;
#endif

#ifndef __REACTOS__
    if (have_sse2 && ((uintptr_t)buf1 & 0xf) == 0 && ((uintptr_t)buf2 & 0xf) == 0) {
        while (len >= 16) {
            x1 = _mm_load_si128((__m128i*)buf1);
            x2 = _mm_load_si128((__m128i*)buf2);
            x1 = _mm_xor_si128(x1, x2);
            _mm_store_si128((__m128i*)buf1, x1);

            buf1 += 16;
            buf2 += 16;
            len -= 16;
        }
    }
#endif

    for (j = 0; j < len; j++) {
        *buf1 ^= *buf2;
        buf1++;
        buf2++;
    }
}