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
typedef  TYPE_1__* soapMappingPtr ;
struct TYPE_3__ {int /*<<< orphan*/  to_zval; int /*<<< orphan*/  to_xml; } ;

/* Variables and functions */
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void delete_mapping(void *data)
{
	soapMappingPtr map = (soapMappingPtr)data;

	zval_ptr_dtor(&map->to_xml);
	zval_ptr_dtor(&map->to_zval);
	efree(map);
}