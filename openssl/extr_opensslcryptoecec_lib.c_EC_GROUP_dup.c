#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  meth; } ;
typedef  TYPE_1__ EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  EC_GROUP_copy (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  EC_GROUP_free (TYPE_1__*) ; 
 TYPE_1__* EC_GROUP_new (int /*<<< orphan*/ ) ; 

EC_GROUP *EC_GROUP_dup(const EC_GROUP *a)
{
    EC_GROUP *t = NULL;
    int ok = 0;

    if (a == NULL)
        return NULL;

    if ((t = EC_GROUP_new(a->meth)) == NULL)
        return NULL;
    if (!EC_GROUP_copy(t, a))
        goto err;

    ok = 1;

 err:
    if (!ok) {
        EC_GROUP_free(t);
        return NULL;
    }
        return t;
}