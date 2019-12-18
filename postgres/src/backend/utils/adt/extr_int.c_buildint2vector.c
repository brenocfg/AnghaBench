#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ndim; int dim1; scalar_t__ lbound1; int /*<<< orphan*/  elemtype; scalar_t__ dataoffset; int /*<<< orphan*/  values; } ;
typedef  TYPE_1__ int2vector ;
typedef  int /*<<< orphan*/  int16 ;

/* Variables and functions */
 int /*<<< orphan*/  INT2OID ; 
 int /*<<< orphan*/  Int2VectorSize (int) ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ palloc0 (int /*<<< orphan*/ ) ; 

int2vector *
buildint2vector(const int16 *int2s, int n)
{
	int2vector *result;

	result = (int2vector *) palloc0(Int2VectorSize(n));

	if (n > 0 && int2s)
		memcpy(result->values, int2s, n * sizeof(int16));

	/*
	 * Attach standard array header.  For historical reasons, we set the index
	 * lower bound to 0 not 1.
	 */
	SET_VARSIZE(result, Int2VectorSize(n));
	result->ndim = 1;
	result->dataoffset = 0;		/* never any nulls */
	result->elemtype = INT2OID;
	result->dim1 = n;
	result->lbound1 = 0;

	return result;
}