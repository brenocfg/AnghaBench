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
typedef  size_t u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int hi; int lo; } ;
typedef  TYPE_1__ u128 ;

/* Variables and functions */
 int /*<<< orphan*/  PUTU32 (size_t*,scalar_t__) ; 
 int* rem_4bit ; 

__attribute__((used)) static void gcm_ghash_4bit(u64 Xi[2], const u128 Htable[16],
                           const u8 *inp, size_t len)
{
    u128 Z;
    int cnt;
    size_t rem, nlo, nhi;
    const union {
        long one;
        char little;
    } is_endian = { 1 };

#   if 1
    do {
        cnt = 15;
        nlo = ((const u8 *)Xi)[15];
        nlo ^= inp[15];
        nhi = nlo >> 4;
        nlo &= 0xf;

        Z.hi = Htable[nlo].hi;
        Z.lo = Htable[nlo].lo;

        while (1) {
            rem = (size_t)Z.lo & 0xf;
            Z.lo = (Z.hi << 60) | (Z.lo >> 4);
            Z.hi = (Z.hi >> 4);
            if (sizeof(size_t) == 8)
                Z.hi ^= rem_4bit[rem];
            else
                Z.hi ^= (u64)rem_4bit[rem] << 32;

            Z.hi ^= Htable[nhi].hi;
            Z.lo ^= Htable[nhi].lo;

            if (--cnt < 0)
                break;

            nlo = ((const u8 *)Xi)[cnt];
            nlo ^= inp[cnt];
            nhi = nlo >> 4;
            nlo &= 0xf;

            rem = (size_t)Z.lo & 0xf;
            Z.lo = (Z.hi << 60) | (Z.lo >> 4);
            Z.hi = (Z.hi >> 4);
            if (sizeof(size_t) == 8)
                Z.hi ^= rem_4bit[rem];
            else
                Z.hi ^= (u64)rem_4bit[rem] << 32;

            Z.hi ^= Htable[nlo].hi;
            Z.lo ^= Htable[nlo].lo;
        }
#   else
    /*
     * Extra 256+16 bytes per-key plus 512 bytes shared tables
     * [should] give ~50% improvement... One could have PACK()-ed
     * the rem_8bit even here, but the priority is to minimize
     * cache footprint...
     */
    u128 Hshr4[16];             /* Htable shifted right by 4 bits */
    u8 Hshl4[16];               /* Htable shifted left by 4 bits */
    static const unsigned short rem_8bit[256] = {
        0x0000, 0x01C2, 0x0384, 0x0246, 0x0708, 0x06CA, 0x048C, 0x054E,
        0x0E10, 0x0FD2, 0x0D94, 0x0C56, 0x0918, 0x08DA, 0x0A9C, 0x0B5E,
        0x1C20, 0x1DE2, 0x1FA4, 0x1E66, 0x1B28, 0x1AEA, 0x18AC, 0x196E,
        0x1230, 0x13F2, 0x11B4, 0x1076, 0x1538, 0x14FA, 0x16BC, 0x177E,
        0x3840, 0x3982, 0x3BC4, 0x3A06, 0x3F48, 0x3E8A, 0x3CCC, 0x3D0E,
        0x3650, 0x3792, 0x35D4, 0x3416, 0x3158, 0x309A, 0x32DC, 0x331E,
        0x2460, 0x25A2, 0x27E4, 0x2626, 0x2368, 0x22AA, 0x20EC, 0x212E,
        0x2A70, 0x2BB2, 0x29F4, 0x2836, 0x2D78, 0x2CBA, 0x2EFC, 0x2F3E,
        0x7080, 0x7142, 0x7304, 0x72C6, 0x7788, 0x764A, 0x740C, 0x75CE,
        0x7E90, 0x7F52, 0x7D14, 0x7CD6, 0x7998, 0x785A, 0x7A1C, 0x7BDE,
        0x6CA0, 0x6D62, 0x6F24, 0x6EE6, 0x6BA8, 0x6A6A, 0x682C, 0x69EE,
        0x62B0, 0x6372, 0x6134, 0x60F6, 0x65B8, 0x647A, 0x663C, 0x67FE,
        0x48C0, 0x4902, 0x4B44, 0x4A86, 0x4FC8, 0x4E0A, 0x4C4C, 0x4D8E,
        0x46D0, 0x4712, 0x4554, 0x4496, 0x41D8, 0x401A, 0x425C, 0x439E,
        0x54E0, 0x5522, 0x5764, 0x56A6, 0x53E8, 0x522A, 0x506C, 0x51AE,
        0x5AF0, 0x5B32, 0x5974, 0x58B6, 0x5DF8, 0x5C3A, 0x5E7C, 0x5FBE,
        0xE100, 0xE0C2, 0xE284, 0xE346, 0xE608, 0xE7CA, 0xE58C, 0xE44E,
        0xEF10, 0xEED2, 0xEC94, 0xED56, 0xE818, 0xE9DA, 0xEB9C, 0xEA5E,
        0xFD20, 0xFCE2, 0xFEA4, 0xFF66, 0xFA28, 0xFBEA, 0xF9AC, 0xF86E,
        0xF330, 0xF2F2, 0xF0B4, 0xF176, 0xF438, 0xF5FA, 0xF7BC, 0xF67E,
        0xD940, 0xD882, 0xDAC4, 0xDB06, 0xDE48, 0xDF8A, 0xDDCC, 0xDC0E,
        0xD750, 0xD692, 0xD4D4, 0xD516, 0xD058, 0xD19A, 0xD3DC, 0xD21E,
        0xC560, 0xC4A2, 0xC6E4, 0xC726, 0xC268, 0xC3AA, 0xC1EC, 0xC02E,
        0xCB70, 0xCAB2, 0xC8F4, 0xC936, 0xCC78, 0xCDBA, 0xCFFC, 0xCE3E,
        0x9180, 0x9042, 0x9204, 0x93C6, 0x9688, 0x974A, 0x950C, 0x94CE,
        0x9F90, 0x9E52, 0x9C14, 0x9DD6, 0x9898, 0x995A, 0x9B1C, 0x9ADE,
        0x8DA0, 0x8C62, 0x8E24, 0x8FE6, 0x8AA8, 0x8B6A, 0x892C, 0x88EE,
        0x83B0, 0x8272, 0x8034, 0x81F6, 0x84B8, 0x857A, 0x873C, 0x86FE,
        0xA9C0, 0xA802, 0xAA44, 0xAB86, 0xAEC8, 0xAF0A, 0xAD4C, 0xAC8E,
        0xA7D0, 0xA612, 0xA454, 0xA596, 0xA0D8, 0xA11A, 0xA35C, 0xA29E,
        0xB5E0, 0xB422, 0xB664, 0xB7A6, 0xB2E8, 0xB32A, 0xB16C, 0xB0AE,
        0xBBF0, 0xBA32, 0xB874, 0xB9B6, 0xBCF8, 0xBD3A, 0xBF7C, 0xBEBE
    };
    /*
     * This pre-processing phase slows down procedure by approximately
     * same time as it makes each loop spin faster. In other words
     * single block performance is approximately same as straightforward
     * "4-bit" implementation, and then it goes only faster...
     */
    for (cnt = 0; cnt < 16; ++cnt) {
        Z.hi = Htable[cnt].hi;
        Z.lo = Htable[cnt].lo;
        Hshr4[cnt].lo = (Z.hi << 60) | (Z.lo >> 4);
        Hshr4[cnt].hi = (Z.hi >> 4);
        Hshl4[cnt] = (u8)(Z.lo << 4);
    }

    do {
        for (Z.lo = 0, Z.hi = 0, cnt = 15; cnt; --cnt) {
            nlo = ((const u8 *)Xi)[cnt];
            nlo ^= inp[cnt];
            nhi = nlo >> 4;
            nlo &= 0xf;

            Z.hi ^= Htable[nlo].hi;
            Z.lo ^= Htable[nlo].lo;

            rem = (size_t)Z.lo & 0xff;

            Z.lo = (Z.hi << 56) | (Z.lo >> 8);
            Z.hi = (Z.hi >> 8);

            Z.hi ^= Hshr4[nhi].hi;
            Z.lo ^= Hshr4[nhi].lo;
            Z.hi ^= (u64)rem_8bit[rem ^ Hshl4[nhi]] << 48;
        }

        nlo = ((const u8 *)Xi)[0];
        nlo ^= inp[0];
        nhi = nlo >> 4;
        nlo &= 0xf;

        Z.hi ^= Htable[nlo].hi;
        Z.lo ^= Htable[nlo].lo;

        rem = (size_t)Z.lo & 0xf;

        Z.lo = (Z.hi << 60) | (Z.lo >> 4);
        Z.hi = (Z.hi >> 4);

        Z.hi ^= Htable[nhi].hi;
        Z.lo ^= Htable[nhi].lo;
        Z.hi ^= ((u64)rem_8bit[rem << 4]) << 48;
#   endif

        if (is_endian.little) {
#   ifdef BSWAP8
            Xi[0] = BSWAP8(Z.hi);
            Xi[1] = BSWAP8(Z.lo);
#   else
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
#   endif
        } else {
            Xi[0] = Z.hi;
            Xi[1] = Z.lo;
        }
    } while (inp += 16, len -= 16);
}