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
typedef  int /*<<< orphan*/  point_conversion_form_t ;
struct TYPE_3__ {int /*<<< orphan*/ * pub_key; int /*<<< orphan*/ * group; } ;
typedef  TYPE_1__ EC_KEY ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 size_t EC_POINT_point2buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char**,int /*<<< orphan*/ *) ; 

size_t EC_KEY_key2buf(const EC_KEY *key, point_conversion_form_t form,
                        unsigned char **pbuf, BN_CTX *ctx)
{
    if (key == NULL || key->pub_key == NULL || key->group == NULL)
        return 0;
    return EC_POINT_point2buf(key->group, key->pub_key, form, pbuf, ctx);
}