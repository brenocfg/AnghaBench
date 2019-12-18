#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ fn_oid; } ;
struct TYPE_4__ {int /*<<< orphan*/  proc; scalar_t__ elem_is_rowtype; TYPE_3__ transform_proc; int /*<<< orphan*/ * elements; scalar_t__* nulls; } ;
typedef  TYPE_1__ plperl_array_info ;
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AV ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 char* OutputFunctionCall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cstr2sv (char*) ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/ * newAV () ; 
 int /*<<< orphan*/ * newRV_noinc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * newSV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * plperl_hash_from_datum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static SV  *
make_array_ref(plperl_array_info *info, int first, int last)
{
	dTHX;
	int			i;
	AV		   *result = newAV();

	for (i = first; i < last; i++)
	{
		if (info->nulls[i])
		{
			/*
			 * We can't use &PL_sv_undef here.  See "AVs, HVs and undefined
			 * values" in perlguts.
			 */
			av_push(result, newSV(0));
		}
		else
		{
			Datum		itemvalue = info->elements[i];

			if (info->transform_proc.fn_oid)
				av_push(result, (SV *) DatumGetPointer(FunctionCall1(&info->transform_proc, itemvalue)));
			else if (info->elem_is_rowtype)
				/* Handle composite type elements */
				av_push(result, plperl_hash_from_datum(itemvalue));
			else
			{
				char	   *val = OutputFunctionCall(&info->proc, itemvalue);

				av_push(result, cstr2sv(val));
			}
		}
	}
	return newRV_noinc((SV *) result);
}