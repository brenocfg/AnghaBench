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
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ EC_KEY_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_METHOD_DYNAMIC ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

EC_KEY_METHOD *EC_KEY_METHOD_new(const EC_KEY_METHOD *meth)
{
    EC_KEY_METHOD *ret = OPENSSL_zalloc(sizeof(*meth));

    if (ret == NULL)
        return NULL;
    if (meth != NULL)
        *ret = *meth;
    ret->flags |= EC_KEY_METHOD_DYNAMIC;
    return ret;
}