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
struct TYPE_3__ {unsigned long* data; int rounds; } ;
typedef  TYPE_1__ RC5_32_KEY ;
typedef  unsigned long RC5_32_INT ;

/* Variables and functions */
 int /*<<< orphan*/  D_RC5_32 (unsigned long,unsigned long,unsigned long*,int) ; 

void RC5_32_decrypt(unsigned long *d, RC5_32_KEY *key)
{
    RC5_32_INT a, b, *s;

    s = key->data;

    a = d[0];
    b = d[1];
    if (key->rounds == 16) {
        D_RC5_32(a, b, s, 32);
        D_RC5_32(a, b, s, 30);
        D_RC5_32(a, b, s, 28);
        D_RC5_32(a, b, s, 26);
        /* Do a full expansion to avoid a jump */
        D_RC5_32(a, b, s, 24);
        D_RC5_32(a, b, s, 22);
        D_RC5_32(a, b, s, 20);
        D_RC5_32(a, b, s, 18);
    } else if (key->rounds == 12) {
        D_RC5_32(a, b, s, 24);
        D_RC5_32(a, b, s, 22);
        D_RC5_32(a, b, s, 20);
        D_RC5_32(a, b, s, 18);
    }
    D_RC5_32(a, b, s, 16);
    D_RC5_32(a, b, s, 14);
    D_RC5_32(a, b, s, 12);
    D_RC5_32(a, b, s, 10);
    D_RC5_32(a, b, s, 8);
    D_RC5_32(a, b, s, 6);
    D_RC5_32(a, b, s, 4);
    D_RC5_32(a, b, s, 2);
    d[0] = a - s[0];
    d[1] = b - s[1];
}