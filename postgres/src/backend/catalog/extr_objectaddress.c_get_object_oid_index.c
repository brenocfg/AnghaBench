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
struct TYPE_3__ {int /*<<< orphan*/  oid_index_oid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectPropertyType ;

/* Variables and functions */
 TYPE_1__* get_object_property_data (int /*<<< orphan*/ ) ; 

Oid
get_object_oid_index(Oid class_id)
{
	const ObjectPropertyType *prop = get_object_property_data(class_id);

	return prop->oid_index_oid;
}