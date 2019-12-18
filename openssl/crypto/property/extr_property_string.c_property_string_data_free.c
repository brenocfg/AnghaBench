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
struct TYPE_3__ {scalar_t__ prop_value_idx; scalar_t__ prop_name_idx; int /*<<< orphan*/  prop_values; int /*<<< orphan*/  prop_names; } ;
typedef  TYPE_1__ PROPERTY_STRING_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  property_table_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void property_string_data_free(void *vpropdata)
{
    PROPERTY_STRING_DATA *propdata = vpropdata;

    if (propdata == NULL)
        return;

    property_table_free(&propdata->prop_names);
    property_table_free(&propdata->prop_values);
    propdata->prop_name_idx = propdata->prop_value_idx = 0;

    OPENSSL_free(propdata);
}