#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* P; int* S; } ;
typedef  int BF_LONG ;
typedef  TYPE_1__ BF_KEY ;

/* Variables and functions */
 int BF_ROUNDS ; 
 int /*<<< orphan*/  BF_encrypt (int*,TYPE_1__*) ; 
 int /*<<< orphan*/  bf_init ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

void BF_set_key(BF_KEY *key, int len, const unsigned char *data)
{
    int i;
    BF_LONG *p, ri, in[2];
    const unsigned char *d, *end;

    memcpy(key, &bf_init, sizeof(BF_KEY));
    p = key->P;

    if (len > ((BF_ROUNDS + 2) * 4))
        len = (BF_ROUNDS + 2) * 4;

    d = data;
    end = &(data[len]);
    for (i = 0; i < (BF_ROUNDS + 2); i++) {
        ri = *(d++);
        if (d >= end)
            d = data;

        ri <<= 8;
        ri |= *(d++);
        if (d >= end)
            d = data;

        ri <<= 8;
        ri |= *(d++);
        if (d >= end)
            d = data;

        ri <<= 8;
        ri |= *(d++);
        if (d >= end)
            d = data;

        p[i] ^= ri;
    }

    in[0] = 0L;
    in[1] = 0L;
    for (i = 0; i < (BF_ROUNDS + 2); i += 2) {
        BF_encrypt(in, key);
        p[i] = in[0];
        p[i + 1] = in[1];
    }

    p = key->S;
    for (i = 0; i < 4 * 256; i += 2) {
        BF_encrypt(in, key);
        p[i] = in[0];
        p[i + 1] = in[1];
    }
}