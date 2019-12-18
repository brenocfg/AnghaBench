#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int hi; int lo; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ u128 ;

/* Variables and functions */
 int BSWAP8 (long const) ; 
 int GETU32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PUTU32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  REDUCE1BIT (TYPE_1__) ; 

__attribute__((used)) static void gcm_gmult_1bit(u64 Xi[2], const u64 H[2])
{
    u128 V, Z = { 0, 0 };
    long X;
    int i, j;
    const long *xi = (const long *)Xi;
    const union {
        long one;
        char little;
    } is_endian = { 1 };

    V.hi = H[0];                /* H is in host byte order, no byte swapping */
    V.lo = H[1];

    for (j = 0; j < 16 / sizeof(long); ++j) {
        if (is_endian.little) {
            if (sizeof(long) == 8) {
# ifdef BSWAP8
                X = (long)(BSWAP8(xi[j]));
# else
                const u8 *p = (const u8 *)(xi + j);
                X = (long)((u64)GETU32(p) << 32 | GETU32(p + 4));
# endif
            } else {
                const u8 *p = (const u8 *)(xi + j);
                X = (long)GETU32(p);
            }
        } else
            X = xi[j];

        for (i = 0; i < 8 * sizeof(long); ++i, X <<= 1) {
            u64 M = (u64)(X >> (8 * sizeof(long) - 1));
            Z.hi ^= V.hi & M;
            Z.lo ^= V.lo & M;

            REDUCE1BIT(V);
        }
    }

    if (is_endian.little) {
# ifdef BSWAP8
        Xi[0] = BSWAP8(Z.hi);
        Xi[1] = BSWAP8(Z.lo);
# else
        u8 *p = (u8 *)Xi;
        u32 v;
        v = (u32)(Z.hi >> 32);
        PUTU32(p, v);
        v = (u32)(Z.hi);
        PUTU32(p + 4, v);
        v = (u32)(Z.lo >> 32);
        PUTU32(p + 8, v);
        v = (u32)(Z.lo);
        PUTU32(p + 12, v);
# endif
    } else {
        Xi[0] = Z.hi;
        Xi[1] = Z.lo;
    }
}