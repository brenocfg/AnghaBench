#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* curve448_scalar_t ;
typedef  int c448_word_t ;
typedef  int c448_dword_t ;
struct TYPE_6__ {int* limb; } ;
struct TYPE_5__ {int* limb; } ;

/* Variables and functions */
 unsigned int C448_SCALAR_LIMBS ; 
 int C448_WORD_BITS ; 
 int WBITS ; 
 TYPE_2__* sc_p ; 

void curve448_scalar_halve(curve448_scalar_t out, const curve448_scalar_t a)
{
    c448_word_t mask = 0 - (a->limb[0] & 1);
    c448_dword_t chain = 0;
    unsigned int i;

    for (i = 0; i < C448_SCALAR_LIMBS; i++) {
        chain = (chain + a->limb[i]) + (sc_p->limb[i] & mask);
        out->limb[i] = (c448_word_t)chain;
        chain >>= C448_WORD_BITS;
    }
    for (i = 0; i < C448_SCALAR_LIMBS - 1; i++)
        out->limb[i] = out->limb[i] >> 1 | out->limb[i + 1] << (WBITS - 1);
    out->limb[i] = out->limb[i] >> 1 | (c448_word_t)(chain << (WBITS - 1));
}