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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {scalar_t__ i32; scalar_t__ i64; scalar_t__ u32; scalar_t__ u64; double d; int /*<<< orphan*/  size; int /*<<< orphan*/  ref; int /*<<< orphan*/  datum; int /*<<< orphan*/  param; int /*<<< orphan*/  valid_d; int /*<<< orphan*/  valid_u64; int /*<<< orphan*/  valid_u32; int /*<<< orphan*/  valid_i64; int /*<<< orphan*/  valid_i32; } ;
typedef  TYPE_1__ PARAM_CONVERSION ;

/* Variables and functions */
 int OSSL_PARAM_get_double (int /*<<< orphan*/ ,double*) ; 
 int OSSL_PARAM_get_int32 (int /*<<< orphan*/ ,scalar_t__*) ; 
 int OSSL_PARAM_get_int64 (int /*<<< orphan*/ ,scalar_t__*) ; 
 int OSSL_PARAM_get_uint32 (int /*<<< orphan*/ ,scalar_t__*) ; 
 int OSSL_PARAM_get_uint64 (int /*<<< orphan*/ ,scalar_t__*) ; 
 int OSSL_PARAM_set_double (int /*<<< orphan*/ ,double) ; 
 int OSSL_PARAM_set_int32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int OSSL_PARAM_set_int64 (int /*<<< orphan*/ ,scalar_t__) ; 
 int OSSL_PARAM_set_uint32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int OSSL_PARAM_set_uint64 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TEST_false (int) ; 
 int /*<<< orphan*/  TEST_mem_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_note (char*,int) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int param_conversion_test(const PARAM_CONVERSION *pc, int line)
{
    int32_t i32;
    int64_t i64;
    uint32_t u32;
    uint64_t u64;
    double d;

    if (!pc->valid_i32) {
        if (!TEST_false(OSSL_PARAM_get_int32(pc->param, &i32))) {
            TEST_note("unexpected valid conversion to int32 on line %d", line);
            return 0;
        }
    } else {
        if (!TEST_true(OSSL_PARAM_get_int32(pc->param, &i32))
            || !TEST_true(i32 == pc->i32)) {
            TEST_note("unexpected conversion to int32 on line %d", line);
            return 0;
        }
        memset(pc->datum, 44, pc->size);
        if (!TEST_true(OSSL_PARAM_set_int32(pc->param, i32))
            || !TEST_mem_eq(pc->datum, pc->size, pc->ref, pc->size)) {
            TEST_note("unexpected valid conversion from int32 on line %d",
                      line);
            return 0;
        }
    }

    if (!pc->valid_i64) {
        if (!TEST_false(OSSL_PARAM_get_int64(pc->param, &i64))) {
            TEST_note("unexpected valid conversion to int64 on line %d", line);
            return 0;
        }
    } else {
        if (!TEST_true(OSSL_PARAM_get_int64(pc->param, &i64))
            || !TEST_true(i64 == pc->i64)) {
            TEST_note("unexpected conversion to int64 on line %d", line);
            return 0;
        }
        memset(pc->datum, 44, pc->size);
        if (!TEST_true(OSSL_PARAM_set_int64(pc->param, i64))
            || !TEST_mem_eq(pc->datum, pc->size, pc->ref, pc->size)) {
            TEST_note("unexpected valid conversion from int64 on line %d",
                      line);
            return 0;
        }
    }

    if (!pc->valid_u32) {
        if (!TEST_false(OSSL_PARAM_get_uint32(pc->param, &u32))) {
            TEST_note("unexpected valid conversion to uint32 on line %d", line);
            return 0;
        }
    } else {
        if (!TEST_true(OSSL_PARAM_get_uint32(pc->param, &u32))
            || !TEST_true(u32 == pc->u32)) {
            TEST_note("unexpected conversion to uint32 on line %d", line);
            return 0;
        }
        memset(pc->datum, 44, pc->size);
        if (!TEST_true(OSSL_PARAM_set_uint32(pc->param, u32))
            || !TEST_mem_eq(pc->datum, pc->size, pc->ref, pc->size)) {
            TEST_note("unexpected valid conversion from uint32 on line %d",
                      line);
            return 0;
        }
    }

    if (!pc->valid_u64) {
        if (!TEST_false(OSSL_PARAM_get_uint64(pc->param, &u64))) {
            TEST_note("unexpected valid conversion to uint64 on line %d", line);
            return 0;
        }
    } else {
        if (!TEST_true(OSSL_PARAM_get_uint64(pc->param, &u64))
            || !TEST_true(u64 == pc->u64)) {
            TEST_note("unexpected conversion to uint64 on line %d", line);
            return 0;
        }
        memset(pc->datum, 44, pc->size);
        if (!TEST_true(OSSL_PARAM_set_uint64(pc->param, u64))
            || !TEST_mem_eq(pc->datum, pc->size, pc->ref, pc->size)) {
            TEST_note("unexpected valid conversion from uint64 on line %d",
                      line);
            return 0;
        }
    }

    if (!pc->valid_d) {
        if (!TEST_false(OSSL_PARAM_get_double(pc->param, &d))) {
            TEST_note("unexpected valid conversion to double on line %d", line);
            return 0;
        }
    } else {
        if (!TEST_true(OSSL_PARAM_get_double(pc->param, &d))
            || !TEST_true(d == pc->d)) {
            TEST_note("unexpected conversion to double on line %d", line);
            return 0;
        }
        memset(pc->datum, 44, pc->size);
        if (!TEST_true(OSSL_PARAM_set_double(pc->param, d))
            || !TEST_mem_eq(pc->datum, pc->size, pc->ref, pc->size)) {
            TEST_note("unexpected valid conversion from double on line %d",
                      line);
            return 0;
        }
    }

    return 1;
}