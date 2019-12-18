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
struct TYPE_4__ {scalar_t__ data_type; int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  OPENSSL_secure_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OSSL_PARAM_ALLOCATED_END ; 

void ossl_param_bld_free(OSSL_PARAM *params)
{
    if (params != NULL) {
        OSSL_PARAM *p;

        for (p = params; p->key != NULL; p++)
            ;
        if (p->data_type == OSSL_PARAM_ALLOCATED_END)
            OPENSSL_secure_clear_free(p->data, p->data_size);
        OPENSSL_free(params);
    }
}