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
typedef  int u32 ;
typedef  size_t s3 ;
typedef  size_t s2 ;
typedef  size_t s1 ;
typedef  size_t s0 ;
struct TYPE_3__ {int* rd_key; int rounds; } ;
typedef  TYPE_1__ AES_KEY ;

/* Variables and functions */
 int const GETU32 (unsigned char const*) ; 
 int const* Te0 ; 
 int const* Te1 ; 
 int const* Te2 ; 
 int const* Te3 ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void AES_encrypt(const unsigned char *in, unsigned char *out,
                 const AES_KEY *key)
{

    const u32 *rk;
    u32 s0, s1, s2, s3, t[4];
    int r;

    assert(in && out && key);
    rk = key->rd_key;

    /*
     * map byte array block to cipher state
     * and add initial round key:
     */
    s0 = GETU32(in     ) ^ rk[0];
    s1 = GETU32(in +  4) ^ rk[1];
    s2 = GETU32(in +  8) ^ rk[2];
    s3 = GETU32(in + 12) ^ rk[3];

#if defined(AES_COMPACT_IN_OUTER_ROUNDS)
    prefetch256(Te4);

    t[0] = (u32)Te4[(s0      ) & 0xff]       ^
           (u32)Te4[(s1 >>  8) & 0xff] <<  8 ^
           (u32)Te4[(s2 >> 16) & 0xff] << 16 ^
           (u32)Te4[(s3 >> 24)       ] << 24;
    t[1] = (u32)Te4[(s1      ) & 0xff]       ^
           (u32)Te4[(s2 >>  8) & 0xff] <<  8 ^
           (u32)Te4[(s3 >> 16) & 0xff] << 16 ^
           (u32)Te4[(s0 >> 24)       ] << 24;
    t[2] = (u32)Te4[(s2      ) & 0xff]       ^
           (u32)Te4[(s3 >>  8) & 0xff] <<  8 ^
           (u32)Te4[(s0 >> 16) & 0xff] << 16 ^
           (u32)Te4[(s1 >> 24)       ] << 24;
    t[3] = (u32)Te4[(s3      ) & 0xff]       ^
           (u32)Te4[(s0 >>  8) & 0xff] <<  8 ^
           (u32)Te4[(s1 >> 16) & 0xff] << 16 ^
           (u32)Te4[(s2 >> 24)       ] << 24;

    /* now do the linear transform using words */
    {   int i;
        u32 r0, r1, r2;

        for (i = 0; i < 4; i++) {
            r0 = t[i];
            r1 = r0 & 0x80808080;
            r2 = ((r0 & 0x7f7f7f7f) << 1) ^
                ((r1 - (r1 >> 7)) & 0x1b1b1b1b);
#if defined(ROTATE)
            t[i] = r2 ^ ROTATE(r2,24) ^ ROTATE(r0,24) ^
                ROTATE(r0,16) ^ ROTATE(r0,8);
#else
            t[i] = r2 ^ ((r2 ^ r0) << 24) ^ ((r2 ^ r0) >> 8) ^
                (r0 << 16) ^ (r0 >> 16) ^
                (r0 << 8) ^ (r0 >> 24);
#endif
            t[i] ^= rk[4+i];
        }
    }
#else
    t[0] =  Te0[(s0      ) & 0xff] ^
        Te1[(s1 >>  8) & 0xff] ^
        Te2[(s2 >> 16) & 0xff] ^
        Te3[(s3 >> 24)       ] ^
        rk[4];
    t[1] =  Te0[(s1      ) & 0xff] ^
        Te1[(s2 >>  8) & 0xff] ^
        Te2[(s3 >> 16) & 0xff] ^
        Te3[(s0 >> 24)       ] ^
        rk[5];
    t[2] =  Te0[(s2      ) & 0xff] ^
        Te1[(s3 >>  8) & 0xff] ^
        Te2[(s0 >> 16) & 0xff] ^
        Te3[(s1 >> 24)       ] ^
        rk[6];
    t[3] =  Te0[(s3      ) & 0xff] ^
        Te1[(s0 >>  8) & 0xff] ^
        Te2[(s1 >> 16) & 0xff] ^
        Te3[(s2 >> 24)       ] ^
        rk[7];
#endif
    s0 = t[0]; s1 = t[1]; s2 = t[2]; s3 = t[3];

    /*
     * Nr - 2 full rounds:
     */
    for (rk+=8,r=key->rounds-2; r>0; rk+=4,r--) {
#if defined(AES_COMPACT_IN_INNER_ROUNDS)
        t[0] = (u32)Te4[(s0      ) & 0xff]       ^
               (u32)Te4[(s1 >>  8) & 0xff] <<  8 ^
               (u32)Te4[(s2 >> 16) & 0xff] << 16 ^
               (u32)Te4[(s3 >> 24)       ] << 24;
        t[1] = (u32)Te4[(s1      ) & 0xff]       ^
               (u32)Te4[(s2 >>  8) & 0xff] <<  8 ^
               (u32)Te4[(s3 >> 16) & 0xff] << 16 ^
               (u32)Te4[(s0 >> 24)       ] << 24;
        t[2] = (u32)Te4[(s2      ) & 0xff]       ^
               (u32)Te4[(s3 >>  8) & 0xff] <<  8 ^
               (u32)Te4[(s0 >> 16) & 0xff] << 16 ^
               (u32)Te4[(s1 >> 24)       ] << 24;
        t[3] = (u32)Te4[(s3      ) & 0xff]       ^
               (u32)Te4[(s0 >>  8) & 0xff] <<  8 ^
               (u32)Te4[(s1 >> 16) & 0xff] << 16 ^
               (u32)Te4[(s2 >> 24)       ] << 24;

        /* now do the linear transform using words */
        {
            int i;
            u32 r0, r1, r2;

            for (i = 0; i < 4; i++) {
                r0 = t[i];
                r1 = r0 & 0x80808080;
                r2 = ((r0 & 0x7f7f7f7f) << 1) ^
                    ((r1 - (r1 >> 7)) & 0x1b1b1b1b);
#if defined(ROTATE)
                t[i] = r2 ^ ROTATE(r2,24) ^ ROTATE(r0,24) ^
                    ROTATE(r0,16) ^ ROTATE(r0,8);
#else
                t[i] = r2 ^ ((r2 ^ r0) << 24) ^ ((r2 ^ r0) >> 8) ^
                    (r0 << 16) ^ (r0 >> 16) ^
                    (r0 << 8) ^ (r0 >> 24);
#endif
                t[i] ^= rk[i];
            }
        }
#else
        t[0] =  Te0[(s0      ) & 0xff] ^
            Te1[(s1 >>  8) & 0xff] ^
            Te2[(s2 >> 16) & 0xff] ^
            Te3[(s3 >> 24)       ] ^
            rk[0];
        t[1] =  Te0[(s1      ) & 0xff] ^
            Te1[(s2 >>  8) & 0xff] ^
            Te2[(s3 >> 16) & 0xff] ^
            Te3[(s0 >> 24)       ] ^
            rk[1];
        t[2] =  Te0[(s2      ) & 0xff] ^
            Te1[(s3 >>  8) & 0xff] ^
            Te2[(s0 >> 16) & 0xff] ^
            Te3[(s1 >> 24)       ] ^
            rk[2];
        t[3] =  Te0[(s3      ) & 0xff] ^
            Te1[(s0 >>  8) & 0xff] ^
            Te2[(s1 >> 16) & 0xff] ^
            Te3[(s2 >> 24)       ] ^
            rk[3];
#endif
        s0 = t[0]; s1 = t[1]; s2 = t[2]; s3 = t[3];
    }
    /*
     * apply last round and
     * map cipher state to byte array block:
     */
#if defined(AES_COMPACT_IN_OUTER_ROUNDS)
    prefetch256(Te4);

    *(u32*)(out+0) =
           (u32)Te4[(s0      ) & 0xff]       ^
           (u32)Te4[(s1 >>  8) & 0xff] <<  8 ^
           (u32)Te4[(s2 >> 16) & 0xff] << 16 ^
           (u32)Te4[(s3 >> 24)       ] << 24 ^
        rk[0];
    *(u32*)(out+4) =
           (u32)Te4[(s1      ) & 0xff]       ^
           (u32)Te4[(s2 >>  8) & 0xff] <<  8 ^
           (u32)Te4[(s3 >> 16) & 0xff] << 16 ^
           (u32)Te4[(s0 >> 24)       ] << 24 ^
        rk[1];
    *(u32*)(out+8) =
           (u32)Te4[(s2      ) & 0xff]       ^
           (u32)Te4[(s3 >>  8) & 0xff] <<  8 ^
           (u32)Te4[(s0 >> 16) & 0xff] << 16 ^
           (u32)Te4[(s1 >> 24)       ] << 24 ^
        rk[2];
    *(u32*)(out+12) =
           (u32)Te4[(s3      ) & 0xff]       ^
           (u32)Te4[(s0 >>  8) & 0xff] <<  8 ^
           (u32)Te4[(s1 >> 16) & 0xff] << 16 ^
           (u32)Te4[(s2 >> 24)       ] << 24 ^
        rk[3];
#else
    *(u32*)(out+0) =
        (Te2[(s0      ) & 0xff] & 0x000000ffU) ^
        (Te3[(s1 >>  8) & 0xff] & 0x0000ff00U) ^
        (Te0[(s2 >> 16) & 0xff] & 0x00ff0000U) ^
        (Te1[(s3 >> 24)       ] & 0xff000000U) ^
        rk[0];
    *(u32*)(out+4) =
        (Te2[(s1      ) & 0xff] & 0x000000ffU) ^
        (Te3[(s2 >>  8) & 0xff] & 0x0000ff00U) ^
        (Te0[(s3 >> 16) & 0xff] & 0x00ff0000U) ^
        (Te1[(s0 >> 24)       ] & 0xff000000U) ^
        rk[1];
    *(u32*)(out+8) =
        (Te2[(s2      ) & 0xff] & 0x000000ffU) ^
        (Te3[(s3 >>  8) & 0xff] & 0x0000ff00U) ^
        (Te0[(s0 >> 16) & 0xff] & 0x00ff0000U) ^
        (Te1[(s1 >> 24)       ] & 0xff000000U) ^
        rk[2];
    *(u32*)(out+12) =
        (Te2[(s3      ) & 0xff] & 0x000000ffU) ^
        (Te3[(s0 >>  8) & 0xff] & 0x0000ff00U) ^
        (Te0[(s1 >> 16) & 0xff] & 0x00ff0000U) ^
        (Te1[(s2 >> 24)       ] & 0xff000000U) ^
        rk[3];
#endif
}