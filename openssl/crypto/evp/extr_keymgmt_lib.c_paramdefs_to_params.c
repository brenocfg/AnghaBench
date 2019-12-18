#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ return_size; int /*<<< orphan*/ * data; int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 TYPE_1__* OPENSSL_zalloc (size_t) ; 

__attribute__((used)) static OSSL_PARAM *paramdefs_to_params(const OSSL_PARAM *paramdefs)
{
    size_t cnt;
    const OSSL_PARAM *p;
    OSSL_PARAM *params = NULL, *q;

    for (cnt = 1, p = paramdefs; p->key != NULL; p++, cnt++)
        continue;

    params = OPENSSL_zalloc(cnt * sizeof(*params));
    if (params == NULL)
        return NULL;

    for (p = paramdefs, q = params; ; p++, q++) {
        *q = *p;
        if (p->key == NULL)
            break;

        q->data = NULL;          /* In case the provider used it */
        q->return_size = 0;
    }

    return params;
}