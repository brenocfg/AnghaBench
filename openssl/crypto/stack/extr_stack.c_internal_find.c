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
struct TYPE_3__ {int num; void const** data; int sorted; int /*<<< orphan*/ * comp; } ;
typedef  TYPE_1__ OPENSSL_STACK ;

/* Variables and functions */
 void* ossl_bsearch (void const**,void const**,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qsort (void const**,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int internal_find(OPENSSL_STACK *st, const void *data,
                         int ret_val_options)
{
    const void *r;
    int i;

    if (st == NULL || st->num == 0)
        return -1;

    if (st->comp == NULL) {
        for (i = 0; i < st->num; i++)
            if (st->data[i] == data)
                return i;
        return -1;
    }

    if (!st->sorted) {
        if (st->num > 1)
            qsort(st->data, st->num, sizeof(void *), st->comp);
        st->sorted = 1; /* empty or single-element stack is considered sorted */
    }
    if (data == NULL)
        return -1;
    r = ossl_bsearch(&data, st->data, st->num, sizeof(void *), st->comp,
                     ret_val_options);

    return r == NULL ? -1 : (int)((const void **)r - st->data);
}