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
struct TYPE_4__ {unsigned long* key; scalar_t__ has_binomial; scalar_t__ has_gauss; scalar_t__ gauss; } ;
typedef  TYPE_1__ rk_state ;
typedef  int npy_intp ;

/* Variables and functions */
 int RK_STATE_LEN ; 
 int /*<<< orphan*/  init_genrand (TYPE_1__*,unsigned long) ; 

extern void
init_by_array(rk_state *self, unsigned long init_key[], npy_intp key_length)
{
    /* was signed in the original code. RDH 12/16/2002 */
    npy_intp i = 1;
    npy_intp j = 0;
    unsigned long *mt = self->key;
    npy_intp k;

    init_genrand(self, 19650218UL);
    k = (RK_STATE_LEN > key_length ? RK_STATE_LEN : key_length);
    for (; k; k--) {
        /* non linear */
        mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * 1664525UL))
            + init_key[j] + j;
        /* for > 32 bit machines */
        mt[i] &= 0xffffffffUL;
        i++;
        j++;
        if (i >= RK_STATE_LEN) {
            mt[0] = mt[RK_STATE_LEN - 1];
            i = 1;
        }
        if (j >= key_length) {
            j = 0;
        }
    }
    for (k = RK_STATE_LEN - 1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
             - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i >= RK_STATE_LEN) {
            mt[0] = mt[RK_STATE_LEN - 1];
            i = 1;
        }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */
    self->gauss = 0;
    self->has_gauss = 0;
    self->has_binomial = 0;
}