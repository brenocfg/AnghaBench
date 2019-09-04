#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* r; scalar_t__* h; } ;
typedef  TYPE_1__ poly1305_internal ;

/* Variables and functions */
 int U8TOU64 (unsigned char const*) ; 

__attribute__((used)) static void poly1305_init(void *ctx, const unsigned char key[16])
{
    poly1305_internal *st = (poly1305_internal *) ctx;

    /* h = 0 */
    st->h[0] = 0;
    st->h[1] = 0;
    st->h[2] = 0;

    /* r &= 0xffffffc0ffffffc0ffffffc0fffffff */
    st->r[0] = U8TOU64(&key[0]) & 0x0ffffffc0fffffff;
    st->r[1] = U8TOU64(&key[8]) & 0x0ffffffc0ffffffc;
}