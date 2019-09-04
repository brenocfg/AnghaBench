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
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (TYPE_1__*) ; 
 TYPE_1__* mp_obj_int_new_mpz () ; 
 int /*<<< orphan*/  mpz_set_from_bytes (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/  const*) ; 

mp_obj_t mp_obj_int_from_bytes_impl(bool big_endian, size_t len, const byte *buf) {
    mp_obj_int_t *o = mp_obj_int_new_mpz();
    mpz_set_from_bytes(&o->mpz, big_endian, len, buf);
    return MP_OBJ_FROM_PTR(o);
}