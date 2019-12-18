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
struct TYPE_3__ {unsigned char const* data; } ;
typedef  TYPE_1__ ASN1_OBJECT ;

/* Variables and functions */

const unsigned char *OBJ_get0_data(const ASN1_OBJECT *obj)
{
    if (obj == NULL)
        return NULL;
    return obj->data;
}