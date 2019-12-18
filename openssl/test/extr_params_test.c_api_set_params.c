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
struct object_st {char* p4; char* p5; char* p6; void* p6_l; void* p5_l; int /*<<< orphan*/  p3; int /*<<< orphan*/  p2; int /*<<< orphan*/  p1; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_BN (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_double (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_int (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_utf8_ptr (int /*<<< orphan*/  const*,char**) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_utf8_string (int /*<<< orphan*/  const*,char**,int) ; 
 int /*<<< orphan*/ * OSSL_PARAM_locate_const (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 void* strlen (char*) ; 

__attribute__((used)) static int api_set_params(void *vobj, const OSSL_PARAM *params)
{
    struct object_st *obj = vobj;
    const OSSL_PARAM *p = NULL;

    if ((p = OSSL_PARAM_locate_const(params, "p1")) != NULL
        && !TEST_true(OSSL_PARAM_get_int(p, &obj->p1)))
        return 0;
    if ((p = OSSL_PARAM_locate_const(params, "p2")) != NULL
        && !TEST_true(OSSL_PARAM_get_double(p, &obj->p2)))
        return 0;
    if ((p = OSSL_PARAM_locate_const(params, "p3")) != NULL
        && !TEST_true(OSSL_PARAM_get_BN(p, &obj->p3)))
        return 0;
    if ((p = OSSL_PARAM_locate_const(params, "p4")) != NULL) {
        OPENSSL_free(obj->p4);
        obj->p4 = NULL;
        /* If the value pointer is NULL, we get it automatically allocated */
        if (!TEST_true(OSSL_PARAM_get_utf8_string(p, &obj->p4, 0)))
            return 0;
    }
    if ((p = OSSL_PARAM_locate_const(params, "p5")) != NULL) {
        char *p5_ptr = obj->p5;
        if (!TEST_true(OSSL_PARAM_get_utf8_string(p, &p5_ptr, sizeof(obj->p5))))
            return 0;
        obj->p5_l = strlen(obj->p5) + 1;
    }
    if ((p = OSSL_PARAM_locate_const(params, "p6")) != NULL) {
        if (!TEST_true(OSSL_PARAM_get_utf8_ptr(p, &obj->p6)))
            return 0;
        obj->p6_l = strlen(obj->p6) + 1;
    }

    return 1;
}