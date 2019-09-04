#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int* rd_key; int rounds; } ;
typedef  TYPE_1__ AES_KEY ;

/* Variables and functions */
 int AES_set_encrypt_key (unsigned char const*,int const,TYPE_1__*) ; 

int AES_set_decrypt_key(const unsigned char *userKey, const int bits,
                        AES_KEY *key)
{

    u32 *rk;
    int i, j, status;
    u32 temp;

    /* first, start with an encryption schedule */
    status = AES_set_encrypt_key(userKey, bits, key);
    if (status < 0)
        return status;

    rk = key->rd_key;

    /* invert the order of the round keys: */
    for (i = 0, j = 4*(key->rounds); i < j; i += 4, j -= 4) {
        temp = rk[i    ]; rk[i    ] = rk[j    ]; rk[j    ] = temp;
        temp = rk[i + 1]; rk[i + 1] = rk[j + 1]; rk[j + 1] = temp;
        temp = rk[i + 2]; rk[i + 2] = rk[j + 2]; rk[j + 2] = temp;
        temp = rk[i + 3]; rk[i + 3] = rk[j + 3]; rk[j + 3] = temp;
    }
    /* apply the inverse MixColumn transform to all round keys but the first and the last: */
    for (i = 1; i < (key->rounds); i++) {
        rk += 4;
#if 1
        for (j = 0; j < 4; j++) {
            u32 tp1, tp2, tp4, tp8, tp9, tpb, tpd, tpe, m;

            tp1 = rk[j];
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
            rk[j] = tpe ^ ROTATE(tpd,16) ^
                ROTATE(tp9,8) ^ ROTATE(tpb,24);
#else
            rk[j] = tpe ^ (tpd >> 16) ^ (tpd << 16) ^
                (tp9 >> 24) ^ (tp9 << 8) ^
                (tpb >> 8) ^ (tpb << 24);
#endif
        }
#else
        rk[0] =
            Td0[Te2[(rk[0]      ) & 0xff] & 0xff] ^
            Td1[Te2[(rk[0] >>  8) & 0xff] & 0xff] ^
            Td2[Te2[(rk[0] >> 16) & 0xff] & 0xff] ^
            Td3[Te2[(rk[0] >> 24)       ] & 0xff];
        rk[1] =
            Td0[Te2[(rk[1]      ) & 0xff] & 0xff] ^
            Td1[Te2[(rk[1] >>  8) & 0xff] & 0xff] ^
            Td2[Te2[(rk[1] >> 16) & 0xff] & 0xff] ^
            Td3[Te2[(rk[1] >> 24)       ] & 0xff];
        rk[2] =
            Td0[Te2[(rk[2]      ) & 0xff] & 0xff] ^
            Td1[Te2[(rk[2] >>  8) & 0xff] & 0xff] ^
            Td2[Te2[(rk[2] >> 16) & 0xff] & 0xff] ^
            Td3[Te2[(rk[2] >> 24)       ] & 0xff];
        rk[3] =
            Td0[Te2[(rk[3]      ) & 0xff] & 0xff] ^
            Td1[Te2[(rk[3] >>  8) & 0xff] & 0xff] ^
            Td2[Te2[(rk[3] >> 16) & 0xff] & 0xff] ^
            Td3[Te2[(rk[3] >> 24)       ] & 0xff];
#endif
    }
    return 0;
}