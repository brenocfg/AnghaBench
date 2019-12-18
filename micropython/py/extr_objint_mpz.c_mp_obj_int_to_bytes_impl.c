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
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_3__ {int /*<<< orphan*/  mpz; } ;
typedef  TYPE_1__ mp_obj_int_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 TYPE_1__* MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mp_obj_is_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_type_int ; 
 int /*<<< orphan*/  mpz_as_bytes (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 

void mp_obj_int_to_bytes_impl(mp_obj_t self_in, bool big_endian, size_t len, byte *buf) {
    assert(mp_obj_is_type(self_in, &mp_type_int));
    mp_obj_int_t *self = MP_OBJ_TO_PTR(self_in);
    memset(buf, 0, len);
    mpz_as_bytes(&self->mpz, big_endian, len, buf);
}