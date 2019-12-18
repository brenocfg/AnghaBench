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
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_get_element (int /*<<< orphan*/ ,int,int*,int,int,int,char,int*) ; 

Datum
array_ref(ArrayType *array, int nSubscripts, int *indx,
		  int arraytyplen, int elmlen, bool elmbyval, char elmalign,
		  bool *isNull)
{
	return array_get_element(PointerGetDatum(array), nSubscripts, indx,
							 arraytyplen, elmlen, elmbyval, elmalign,
							 isNull);
}