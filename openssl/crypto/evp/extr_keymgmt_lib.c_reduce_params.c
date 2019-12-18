#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ return_size; int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 TYPE_1__* OPENSSL_realloc (TYPE_1__*,size_t) ; 

__attribute__((used)) static OSSL_PARAM *reduce_params(OSSL_PARAM *params)
{
    OSSL_PARAM *curr, *next;
    size_t cnt;

    for (cnt = 0, curr = next = params; next->key != NULL; next++) {
        if (next->return_size == 0)
            continue;
        if (curr != next)
            *curr = *next;
        curr++;
        cnt++;
    }
    *curr = *next;               /* Terminating record */
    cnt++;

    curr = OPENSSL_realloc(params, cnt * sizeof(*params));
    if (curr == NULL)
        return params;
    return curr;
}