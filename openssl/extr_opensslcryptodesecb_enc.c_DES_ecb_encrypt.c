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
typedef  unsigned char* const_DES_cblock ;
typedef  int /*<<< orphan*/  DES_key_schedule ;
typedef  unsigned char* DES_cblock ;
typedef  scalar_t__ DES_LONG ;

/* Variables and functions */
 int /*<<< orphan*/  DES_encrypt1 (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  c2l (unsigned char const*,scalar_t__) ; 
 int /*<<< orphan*/  l2c (scalar_t__,unsigned char*) ; 

void DES_ecb_encrypt(const_DES_cblock *input, DES_cblock *output,
                     DES_key_schedule *ks, int enc)
{
    register DES_LONG l;
    DES_LONG ll[2];
    const unsigned char *in = &(*input)[0];
    unsigned char *out = &(*output)[0];

    c2l(in, l);
    ll[0] = l;
    c2l(in, l);
    ll[1] = l;
    DES_encrypt1(ll, ks, enc);
    l = ll[0];
    l2c(l, out);
    l = ll[1];
    l2c(l, out);
    l = ll[0] = ll[1] = 0;
}