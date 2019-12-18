#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ point_conversion_form_t ;
struct TYPE_8__ {TYPE_1__* meth; } ;
struct TYPE_7__ {scalar_t__ conv_form; TYPE_3__* group; int /*<<< orphan*/ * pub_key; } ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_2__ EC_KEY ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int EC_FLAGS_CUSTOM_CURVE ; 
 int /*<<< orphan*/ * EC_POINT_new (TYPE_3__*) ; 
 scalar_t__ EC_POINT_oct2point (TYPE_3__*,int /*<<< orphan*/ *,unsigned char const*,size_t,int /*<<< orphan*/ *) ; 

int EC_KEY_oct2key(EC_KEY *key, const unsigned char *buf, size_t len,
                   BN_CTX *ctx)
{
    if (key == NULL || key->group == NULL)
        return 0;
    if (key->pub_key == NULL)
        key->pub_key = EC_POINT_new(key->group);
    if (key->pub_key == NULL)
        return 0;
    if (EC_POINT_oct2point(key->group, key->pub_key, buf, len, ctx) == 0)
        return 0;
    /*
     * Save the point conversion form.
     * For non-custom curves the first octet of the buffer (excluding
     * the last significant bit) contains the point conversion form.
     * EC_POINT_oct2point() has already performed sanity checking of
     * the buffer so we know it is valid.
     */
    if ((key->group->meth->flags & EC_FLAGS_CUSTOM_CURVE) == 0)
        key->conv_form = (point_conversion_form_t)(buf[0] & ~0x01);
    return 1;
}