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
struct object_st {int /*<<< orphan*/  p6; int /*<<< orphan*/  p5; int /*<<< orphan*/  p4; int /*<<< orphan*/  p3; int /*<<< orphan*/  p2; int /*<<< orphan*/  p1; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/ * OSSL_PARAM_locate (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_BN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_utf8_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_utf8_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int api_get_params(void *vobj, OSSL_PARAM *params)
{
    struct object_st *obj = vobj;
    OSSL_PARAM *p = NULL;

    if ((p = OSSL_PARAM_locate(params, "p1")) != NULL
        && !TEST_true(OSSL_PARAM_set_int(p, obj->p1)))
        return 0;
    if ((p = OSSL_PARAM_locate(params, "p2")) != NULL
        && !TEST_true(OSSL_PARAM_set_double(p, obj->p2)))
        return 0;
    if ((p = OSSL_PARAM_locate(params, "p3")) != NULL
        && !TEST_true(OSSL_PARAM_set_BN(p, obj->p3)))
        return 0;
    if ((p = OSSL_PARAM_locate(params, "p4")) != NULL
        && !TEST_true(OSSL_PARAM_set_utf8_string(p, obj->p4)))
        return 0;
    if ((p = OSSL_PARAM_locate(params, "p5")) != NULL
        && !TEST_true(OSSL_PARAM_set_utf8_string(p, obj->p5)))
        return 0;
    if ((p = OSSL_PARAM_locate(params, "p6")) != NULL
        && !TEST_true(OSSL_PARAM_set_utf8_ptr(p, obj->p6)))
        return 0;

    return 1;
}