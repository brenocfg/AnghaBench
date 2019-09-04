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
typedef  scalar_t__ CAST_LONG ;
typedef  int /*<<< orphan*/  CAST_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_decrypt (scalar_t__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  CAST_encrypt (scalar_t__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  l2n (scalar_t__,unsigned char*) ; 
 int /*<<< orphan*/  n2l (unsigned char const*,scalar_t__) ; 

void CAST_ecb_encrypt(const unsigned char *in, unsigned char *out,
                      const CAST_KEY *ks, int enc)
{
    CAST_LONG l, d[2];

    n2l(in, l);
    d[0] = l;
    n2l(in, l);
    d[1] = l;
    if (enc)
        CAST_encrypt(d, ks);
    else
        CAST_decrypt(d, ks);
    l = d[0];
    l2n(l, out);
    l = d[1];
    l2n(l, out);
    l = d[0] = d[1] = 0;
}