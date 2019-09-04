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
 int const* Td0 ; 
 int const* Td1 ; 
 int const* Td2 ; 
 int const* Td3 ; 
 scalar_t__* Td4 ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch256 (scalar_t__*) ; 

void AES_decrypt(const unsigned char *in, unsigned char *out,
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
    prefetch256(Td4);

    t[0] = (u32)Td4[(s0      ) & 0xff]       ^
           (u32)Td4[(s3 >>  8) & 0xff] <<  8 ^
           (u32)Td4[(s2 >> 16) & 0xff] << 16 ^
           (u32)Td4[(s1 >> 24)       ] << 24;
    t[1] = (u32)Td4[(s1      ) & 0xff]       ^
           (u32)Td4[(s0 >>  8) & 0xff] <<  8 ^
           (u32)Td4[(s3 >> 16) & 0xff] << 16 ^
           (u32)Td4[(s2 >> 24)       ] << 24;
    t[2] = (u32)Td4[(s2      ) & 0xff]       ^
           (u32)Td4[(s1 >>  8) & 0xff] <<  8 ^
           (u32)Td4[(s0 >> 16) & 0xff] << 16 ^
           (u32)Td4[(s3 >> 24)       ] << 24;
    t[3] = (u32)Td4[(s3      ) & 0xff]       ^
           (u32)Td4[(s2 >>  8) & 0xff] <<  8 ^
           (u32)Td4[(s1 >> 16) & 0xff] << 16 ^
           (u32)Td4[(s0 >> 24)       ] << 24;

    /* now do the linear transform using words */
    {
        int i;
        u32 tp1, tp2, tp4, tp8, tp9, tpb, tpd, tpe, m;

        for (i = 0; i < 4; i++) {
            tp1 = t[i];
            m = tp1 & 0x80808080;
            tp2 = ((tp1 & 0x7f7f7f7f) << 1) ^
                ((m - (m >> 7)) & 0x1b1b1b1b);
            m = tp2 & 0x80808080;
            tp4 = ((tp2 & 0x7f7f7f7f) << 1) ^
                ((m - (m >> 7)) & 0x1b1b1b1b);
            m = tp4 & 0x80808080;
            tp8 = ((tp4 & 0x7f7f7f7f) << 1) ^
                ((m - (m >> 7)) & 0x1b1b1b1b);
            tp9 = tp8 ^ tp1;
            tpb = tp9 ^ tp2;
            tpd = tp9 ^ tp4;
            tpe = tp8 ^ tp4 ^ tp2;
#if defined(ROTATE)
            t[i] = tpe ^ ROTATE(tpd,16) ^
                ROTATE(tp9,8) ^ ROTATE(tpb,24);
#else
            t[i] = tpe ^ (tpd >> 16) ^ (tpd << 16) ^
                (tp9 >> 24) ^ (tp9 << 8) ^
                (tpb >> 8) ^ (tpb << 24);
#endif
            t[i] ^= rk[4+i];
        }
    }
#else
    t[0] =  Td0[(s0      ) & 0xff] ^
        Td1[(s3 >>  8) & 0xff] ^
        Td2[(s2 >> 16) & 0xff] ^
        Td3[(s1 >> 24)       ] ^
        rk[4];
    t[1] =  Td0[(s1      ) & 0xff] ^
        Td1[(s0 >>  8) & 0xff] ^
        Td2[(s3 >> 16) & 0xff] ^
        Td3[(s2 >> 24)       ] ^
        rk[5];
    t[2] =  Td0[(s2      ) & 0xff] ^
        Td1[(s1 >>  8) & 0xff] ^
        Td2[(s0 >> 16) & 0xff] ^
        Td3[(s3 >> 24)       ] ^
        rk[6];
    t[3] =  Td0[(s3      ) & 0xff] ^
        Td1[(s2 >>  8) & 0xff] ^
        Td2[(s1 >> 16) & 0xff] ^
        Td3[(s0 >> 24)       ] ^
        rk[7];
#endif
    s0 = t[0]; s1 = t[1]; s2 = t[2]; s3 = t[3];

    /*
     * Nr - 2 full rounds:
     */
    for (rk+=8,r=key->rounds-2; r>0; rk+=4,r--) {
#if defined(AES_COMPACT_IN_INNER_ROUNDS)
        t[0] = (u32)Td4[(s0      ) & 0xff]       ^
               (u32)Td4[(s3 >>  8) & 0xff] <<  8 ^
               (u32)Td4[(s2 >> 16) & 0xff] << 16 ^
               (u32)Td4[(s1 >> 24)       ] << 24;
        t[1] = (u32)Td4[(s1      ) & 0xff]       ^
               (u32)Td4[(s0 >>  8) & 0xff] <<  8 ^
               (u32)Td4[(s3 >> 16) & 0xff] << 16 ^
               (u32)Td4[(s2 >> 24)       ] << 24;
        t[2] = (u32)Td4[(s2      ) & 0xff]       ^
               (u32)Td4[(s1 >>  8) & 0xff] <<  8 ^
               (u32)Td4[(s0 >> 16) & 0xff] << 16 ^
               (u32)Td4[(s3 >> 24)       ] << 24;
        t[3] = (u32)Td4[(s3      ) & 0xff]       ^
               (u32)Td4[(s2 >>  8) & 0xff] <<  8 ^
               (u32)Td4[(s1 >> 16) & 0xff] << 16 ^
               (u32)Td4[(s0 >> 24)       ] << 24;

    /* now do the linear transform using words */
    {
        int i;
        u32 tp1, tp2, tp4, tp8, tp9, tpb, tpd, tpe, m;

        for (i = 0; i < 4; i++) {
            tp1 = t[i];
            m = tp1 & 0x80808080;
            tp2 = ((tp1 & 0x7f7f7f7f) << 1) ^
                ((m - (m >> 7)) & 0x1b1b1b1b);
            m = tp2 & 0x80808080;
            tp4 = ((tp2 & 0x7f7f7f7f) << 1) ^
                ((m - (m >> 7)) & 0x1b1b1b1b);
            m = tp4 & 0x80808080;
            tp8 = ((tp4 & 0x7f7f7f7f) << 1) ^
                ((m - (m >> 7)) & 0x1b1b1b1b);
            tp9 = tp8 ^ tp1;
            tpb = tp9 ^ tp2;
            tpd = tp9 ^ tp4;
            tpe = tp8 ^ tp4 ^ tp2;
#if defined(ROTATE)
            t[i] = tpe ^ ROTATE(tpd,16) ^
                ROTATE(tp9,8) ^ ROTATE(tpb,24);
#else
            t[i] = tpe ^ (tpd >> 16) ^ (tpd << 16) ^
                (tp9 >> 24) ^ (tp9 << 8) ^
                (tpb >> 8) ^ (tpb << 24);
#endif
            t[i] ^= rk[i];
        }
    }
#else
    t[0] =  Td0[(s0      ) & 0xff] ^
        Td1[(s3 >>  8) & 0xff] ^
        Td2[(s2 >> 16) & 0xff] ^
        Td3[(s1 >> 24)       ] ^
        rk[0];
    t[1] =  Td0[(s1      ) & 0xff] ^
        Td1[(s0 >>  8) & 0xff] ^
        Td2[(s3 >> 16) & 0xff] ^
        Td3[(s2 >> 24)       ] ^
        rk[1];
    t[2] =  Td0[(s2      ) & 0xff] ^
        Td1[(s1 >>  8) & 0xff] ^
        Td2[(s0 >> 16) & 0xff] ^
        Td3[(s3 >> 24)       ] ^
        rk[2];
    t[3] =  Td0[(s3      ) & 0xff] ^
        Td1[(s2 >>  8) & 0xff] ^
        Td2[(s1 >> 16) & 0xff] ^
        Td3[(s0 >> 24)       ] ^
        rk[3];
#endif
    s0 = t[0]; s1 = t[1]; s2 = t[2]; s3 = t[3];
    }
    /*
     * apply last round and
     * map cipher state to byte array block:
     */
    prefetch256(Td4);

    *(u32*)(out+0) =
        ((u32)Td4[(s0      ) & 0xff])    ^
        ((u32)Td4[(s3 >>  8) & 0xff] <<  8) ^
        ((u32)Td4[(s2 >> 16) & 0xff] << 16) ^
        ((u32)Td4[(s1 >> 24)       ] << 24) ^
        rk[0];
    *(u32*)(out+4) =
        ((u32)Td4[(s1      ) & 0xff])     ^
        ((u32)Td4[(s0 >>  8) & 0xff] <<  8) ^
        ((u32)Td4[(s3 >> 16) & 0xff] << 16) ^
        ((u32)Td4[(s2 >> 24)       ] << 24) ^
        rk[1];
    *(u32*)(out+8) =
        ((u32)Td4[(s2      ) & 0xff])     ^
        ((u32)Td4[(s1 >>  8) & 0xff] <<  8) ^
        ((u32)Td4[(s0 >> 16) & 0xff] << 16) ^
        ((u32)Td4[(s3 >> 24)       ] << 24) ^
        rk[2];
    *(u32*)(out+12) =
        ((u32)Td4[(s3      ) & 0xff])     ^
        ((u32)Td4[(s2 >>  8) & 0xff] <<  8) ^
        ((u32)Td4[(s1 >> 16) & 0xff] << 16) ^
        ((u32)Td4[(s0 >> 24)       ] << 24) ^
        rk[3];
}