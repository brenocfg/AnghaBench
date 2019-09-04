#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int len; int exponent; int* rr; } ;
typedef  TYPE_1__ RSAPublicKey ;

/* Variables and functions */
 int RSANUMWORDS ; 
 scalar_t__ geM (TYPE_1__ const*,int*) ; 
 int /*<<< orphan*/  montMul (TYPE_1__ const*,int*,int*,int*) ; 
 int /*<<< orphan*/  subM (TYPE_1__ const*,int*) ; 

__attribute__((used)) static void modpow(const RSAPublicKey* key,
                   uint8_t* inout) {
    uint32_t a[RSANUMWORDS];
    uint32_t aR[RSANUMWORDS];
    uint32_t aaR[RSANUMWORDS];
    uint32_t* aaa = 0;
    int i;

    // Convert from big endian byte array to little endian word array.
    for (i = 0; i < key->len; ++i) {
        uint32_t tmp =
            (inout[((key->len - 1 - i) * 4) + 0] << 24) |
            (inout[((key->len - 1 - i) * 4) + 1] << 16) |
            (inout[((key->len - 1 - i) * 4) + 2] << 8) |
            (inout[((key->len - 1 - i) * 4) + 3] << 0);
        a[i] = tmp;
    }

    if (key->exponent == 65537) {
        aaa = aaR;  // Re-use location.
        montMul(key, aR, a, key->rr);  // aR = a * RR / R mod M
        for (i = 0; i < 16; i += 2) {
            montMul(key, aaR, aR, aR);  // aaR = aR * aR / R mod M
            montMul(key, aR, aaR, aaR);  // aR = aaR * aaR / R mod M
        }
        montMul(key, aaa, aR, a);  // aaa = aR * a / R mod M
    } else if (key->exponent == 3) {
        aaa = aR;  // Re-use location.
        montMul(key, aR, a, key->rr);  /* aR = a * RR / R mod M   */
        montMul(key, aaR, aR, aR);     /* aaR = aR * aR / R mod M */
        montMul(key, aaa, aaR, a);     /* aaa = aaR * a / R mod M */
    }

    // Make sure aaa < mod; aaa is at most 1x mod too large.
    if (geM(key, aaa)) {
        subM(key, aaa);
    }

    // Convert to bigendian byte array
    for (i = key->len - 1; i >= 0; --i) {
        uint32_t tmp = aaa[i];
        *inout++ = tmp >> 24;
        *inout++ = tmp >> 16;
        *inout++ = tmp >> 8;
        *inout++ = tmp >> 0;
    }
}