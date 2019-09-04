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
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_4__ {int /*<<< orphan*/  mpz; } ;
typedef  TYPE_1__ mp_obj_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (TYPE_1__*) ; 
 TYPE_1__* mp_obj_int_new_mpz () ; 
 size_t mpz_set_from_str (int /*<<< orphan*/ *,char const*,size_t,int,unsigned int) ; 

mp_obj_t mp_obj_new_int_from_str_len(const char **str, size_t len, bool neg, unsigned int base) {
    mp_obj_int_t *o = mp_obj_int_new_mpz();
    size_t n = mpz_set_from_str(&o->mpz, *str, len, neg, base);
    *str += n;
    return MP_OBJ_FROM_PTR(o);
}