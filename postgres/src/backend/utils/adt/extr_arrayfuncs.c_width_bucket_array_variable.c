#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_9__ {int typlen; int typbyval; char typalign; int /*<<< orphan*/  cmp_proc_finfo; } ;
typedef  TYPE_2__ TypeCacheEntry ;
struct TYPE_10__ {TYPE_1__* args; } ;
struct TYPE_8__ {int isnull; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 scalar_t__ ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARR_DIMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARR_NDIM (int /*<<< orphan*/ *) ; 
 int ArrayGetNItems (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCallInvoke (TYPE_4__*) ; 
 int /*<<< orphan*/  InitFunctionCallInfoData (TYPE_4__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCAL_FCINFO (TYPE_4__*,int) ; 
 char* att_addlength_pointer (char*,int,char*) ; 
 scalar_t__ att_align_nominal (char*,char) ; 
 int /*<<< orphan*/  fetch_att (char*,int,int) ; 
 TYPE_4__* locfcinfo ; 

__attribute__((used)) static int
width_bucket_array_variable(Datum operand,
							ArrayType *thresholds,
							Oid collation,
							TypeCacheEntry *typentry)
{
	LOCAL_FCINFO(locfcinfo, 2);
	char	   *thresholds_data;
	int			typlen = typentry->typlen;
	bool		typbyval = typentry->typbyval;
	char		typalign = typentry->typalign;
	int			left;
	int			right;

	thresholds_data = (char *) ARR_DATA_PTR(thresholds);

	InitFunctionCallInfoData(*locfcinfo, &typentry->cmp_proc_finfo, 2,
							 collation, NULL, NULL);

	/* Find the bucket */
	left = 0;
	right = ArrayGetNItems(ARR_NDIM(thresholds), ARR_DIMS(thresholds));
	while (left < right)
	{
		int			mid = (left + right) / 2;
		char	   *ptr;
		int			i;
		int32		cmpresult;

		/* Locate mid'th array element by advancing from left element */
		ptr = thresholds_data;
		for (i = left; i < mid; i++)
		{
			ptr = att_addlength_pointer(ptr, typlen, ptr);
			ptr = (char *) att_align_nominal(ptr, typalign);
		}

		locfcinfo->args[0].value = operand;
		locfcinfo->args[0].isnull = false;
		locfcinfo->args[1].value = fetch_att(ptr, typbyval, typlen);
		locfcinfo->args[1].isnull = false;

		cmpresult = DatumGetInt32(FunctionCallInvoke(locfcinfo));

		if (cmpresult < 0)
			right = mid;
		else
		{
			left = mid + 1;

			/*
			 * Move the thresholds pointer to match new "left" index, so we
			 * don't have to seek over those elements again.  This trick
			 * ensures we do only O(N) array indexing work, not O(N^2).
			 */
			ptr = att_addlength_pointer(ptr, typlen, ptr);
			thresholds_data = (char *) att_align_nominal(ptr, typalign);
		}
	}

	return left;
}