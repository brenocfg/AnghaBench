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
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ EVP_ENCODE_CTX ;

/* Variables and functions */
 int EVP_ENCODE_CTX_USE_SRP_ALPHABET ; 
 char conv_bin2ascii (unsigned long,unsigned char const*) ; 
 unsigned char* data_bin2ascii ; 
 unsigned char* srpdata_bin2ascii ; 

__attribute__((used)) static int evp_encodeblock_int(EVP_ENCODE_CTX *ctx, unsigned char *t,
                               const unsigned char *f, int dlen)
{
    int i, ret = 0;
    unsigned long l;
    const unsigned char *table;

    if (ctx != NULL && (ctx->flags & EVP_ENCODE_CTX_USE_SRP_ALPHABET) != 0)
        table = srpdata_bin2ascii;
    else
        table = data_bin2ascii;

    for (i = dlen; i > 0; i -= 3) {
        if (i >= 3) {
            l = (((unsigned long)f[0]) << 16L) |
                (((unsigned long)f[1]) << 8L) | f[2];
            *(t++) = conv_bin2ascii(l >> 18L, table);
            *(t++) = conv_bin2ascii(l >> 12L, table);
            *(t++) = conv_bin2ascii(l >> 6L, table);
            *(t++) = conv_bin2ascii(l, table);
        } else {
            l = ((unsigned long)f[0]) << 16L;
            if (i == 2)
                l |= ((unsigned long)f[1] << 8L);

            *(t++) = conv_bin2ascii(l >> 18L, table);
            *(t++) = conv_bin2ascii(l >> 12L, table);
            *(t++) = (i == 1) ? '=' : conv_bin2ascii(l >> 6L, table);
            *(t++) = '=';
        }
        ret += 4;
        f += 3;
    }

    *t = '\0';
    return ret;
}