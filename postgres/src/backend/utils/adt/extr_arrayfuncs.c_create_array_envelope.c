#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ndim; int dataoffset; int /*<<< orphan*/  elemtype; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  ARR_DIMS (TYPE_1__*) ; 
 int /*<<< orphan*/  ARR_LBOUND (TYPE_1__*) ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static ArrayType *
create_array_envelope(int ndims, int *dimv, int *lbsv, int nbytes,
					  Oid elmtype, int dataoffset)
{
	ArrayType  *result;

	result = (ArrayType *) palloc0(nbytes);
	SET_VARSIZE(result, nbytes);
	result->ndim = ndims;
	result->dataoffset = dataoffset;
	result->elemtype = elmtype;
	memcpy(ARR_DIMS(result), dimv, ndims * sizeof(int));
	memcpy(ARR_LBOUND(result), lbsv, ndims * sizeof(int));

	return result;
}