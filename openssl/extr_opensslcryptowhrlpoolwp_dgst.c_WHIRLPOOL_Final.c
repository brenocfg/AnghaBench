#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  c; } ;
struct TYPE_7__ {unsigned int bitoff; int* data; size_t* bitlen; TYPE_1__ H; } ;
typedef  TYPE_2__ WHIRLPOOL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_cleanse (TYPE_2__*,int) ; 
 int WHIRLPOOL_BBLOCK ; 
 int WHIRLPOOL_COUNTER ; 
 int /*<<< orphan*/  WHIRLPOOL_DIGEST_LENGTH ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  whirlpool_block (TYPE_2__*,int*,int) ; 

int WHIRLPOOL_Final(unsigned char *md, WHIRLPOOL_CTX *c)
{
    unsigned int bitoff = c->bitoff, byteoff = bitoff / 8;
    size_t i, j, v;
    unsigned char *p;

    bitoff %= 8;
    if (bitoff)
        c->data[byteoff] |= 0x80 >> bitoff;
    else
        c->data[byteoff] = 0x80;
    byteoff++;

    /* pad with zeros */
    if (byteoff > (WHIRLPOOL_BBLOCK / 8 - WHIRLPOOL_COUNTER)) {
        if (byteoff < WHIRLPOOL_BBLOCK / 8)
            memset(&c->data[byteoff], 0, WHIRLPOOL_BBLOCK / 8 - byteoff);
        whirlpool_block(c, c->data, 1);
        byteoff = 0;
    }
    if (byteoff < (WHIRLPOOL_BBLOCK / 8 - WHIRLPOOL_COUNTER))
        memset(&c->data[byteoff], 0,
               (WHIRLPOOL_BBLOCK / 8 - WHIRLPOOL_COUNTER) - byteoff);
    /* smash 256-bit c->bitlen in big-endian order */
    p = &c->data[WHIRLPOOL_BBLOCK / 8 - 1]; /* last byte in c->data */
    for (i = 0; i < WHIRLPOOL_COUNTER / sizeof(size_t); i++)
        for (v = c->bitlen[i], j = 0; j < sizeof(size_t); j++, v >>= 8)
            *p-- = (unsigned char)(v & 0xff);

    whirlpool_block(c, c->data, 1);

    if (md) {
        memcpy(md, c->H.c, WHIRLPOOL_DIGEST_LENGTH);
        OPENSSL_cleanse(c, sizeof(*c));
        return 1;
    }
    return 0;
}