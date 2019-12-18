#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  OIDOID ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * lappend_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

List *
oid_array_to_list(Datum datum)
{
	ArrayType  *array = DatumGetArrayTypeP(datum);
	Datum	   *values;
	int			nelems;
	int			i;
	List	   *result = NIL;

	deconstruct_array(array,
					  OIDOID,
					  sizeof(Oid), true, 'i',
					  &values, NULL, &nelems);
	for (i = 0; i < nelems; i++)
		result = lappend_oid(result, values[i]);
	return result;
}