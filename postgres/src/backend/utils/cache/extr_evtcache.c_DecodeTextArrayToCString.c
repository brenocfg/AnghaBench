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
 scalar_t__ ARR_ELEMTYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ ARR_HASNULL (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ TEXTOID ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,scalar_t__,int,int,char,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 char** palloc (int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
DecodeTextArrayToCString(Datum array, char ***cstringp)
{
	ArrayType  *arr = DatumGetArrayTypeP(array);
	Datum	   *elems;
	char	  **cstring;
	int			i;
	int			nelems;

	if (ARR_NDIM(arr) != 1 || ARR_HASNULL(arr) || ARR_ELEMTYPE(arr) != TEXTOID)
		elog(ERROR, "expected 1-D text array");
	deconstruct_array(arr, TEXTOID, -1, false, 'i', &elems, NULL, &nelems);

	cstring = palloc(nelems * sizeof(char *));
	for (i = 0; i < nelems; ++i)
		cstring[i] = TextDatumGetCString(elems[i]);

	pfree(elems);
	*cstringp = cstring;
	return nelems;
}