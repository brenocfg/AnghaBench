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
struct object_st {int p1; double p2; char* p4; char* p5; char* p6; int /*<<< orphan*/  p3; } ;
struct TYPE_3__ {int return_size; scalar_t__ data; int /*<<< orphan*/ * key; int /*<<< orphan*/  data_size; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2nativepad (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 size_t BN_num_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_size_t_ge (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int raw_get_params(void *vobj, OSSL_PARAM *params)
{
    struct object_st *obj = vobj;

    for (; params->key != NULL; params++)
        if (strcmp(params->key, "p1") == 0) {
            params->return_size = sizeof(obj->p1);
            *(int *)params->data = obj->p1;
        } else if (strcmp(params->key, "p2") == 0) {
            params->return_size = sizeof(obj->p2);
            *(double *)params->data = obj->p2;
        } else if (strcmp(params->key, "p3") == 0) {
            size_t bytes = BN_num_bytes(obj->p3);

            params->return_size = bytes;
            if (!TEST_size_t_ge(params->data_size, bytes))
                return 0;
            BN_bn2nativepad(obj->p3, params->data, bytes);
        } else if (strcmp(params->key, "p4") == 0) {
            size_t bytes = strlen(obj->p4) + 1;

            params->return_size = bytes;
            if (!TEST_size_t_ge(params->data_size, bytes))
                return 0;
            strcpy(params->data, obj->p4);
        } else if (strcmp(params->key, "p5") == 0) {
            size_t bytes = strlen(obj->p5) + 1;

            params->return_size = bytes;
            if (!TEST_size_t_ge(params->data_size, bytes))
                return 0;
            strcpy(params->data, obj->p5);
        } else if (strcmp(params->key, "p6") == 0) {
            /*
             * We COULD also use OPENSSL_FULL_VERSION_STR directly and
             * use sizeof(OPENSSL_FULL_VERSION_STR) instead of calling
             * strlen().
             * The caller wouldn't know the difference.
             */
            size_t bytes = strlen(obj->p6) + 1;

            params->return_size = bytes;
            *(const char **)params->data = obj->p6;
        }

    return 1;
}