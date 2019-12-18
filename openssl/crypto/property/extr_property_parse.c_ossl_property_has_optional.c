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
struct TYPE_3__ {scalar_t__ has_optional; } ;
typedef  TYPE_1__ OSSL_PROPERTY_LIST ;

/* Variables and functions */

int ossl_property_has_optional(const OSSL_PROPERTY_LIST *query)
{
    return query->has_optional ? 1 : 0;
}