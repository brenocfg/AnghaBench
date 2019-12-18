#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int16 ;
struct TYPE_7__ {TYPE_1__* es_plannedstmt; TYPE_2__* es_param_exec_vals; } ;
struct TYPE_6__ {int /*<<< orphan*/  isnull; int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int /*<<< orphan*/  paramExecTypes; } ;
typedef  int Size ;
typedef  TYPE_2__ ParamExecData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ EState ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int add_size (int,int) ; 
 int bms_next_member (int /*<<< orphan*/ *,int) ; 
 int datumEstimateSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  get_typlenbyval (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  list_nth_oid (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Size
EstimateParamExecSpace(EState *estate, Bitmapset *params)
{
	int			paramid;
	Size		sz = sizeof(int);

	paramid = -1;
	while ((paramid = bms_next_member(params, paramid)) >= 0)
	{
		Oid			typeOid;
		int16		typLen;
		bool		typByVal;
		ParamExecData *prm;

		prm = &(estate->es_param_exec_vals[paramid]);
		typeOid = list_nth_oid(estate->es_plannedstmt->paramExecTypes,
							   paramid);

		sz = add_size(sz, sizeof(int)); /* space for paramid */

		/* space for datum/isnull */
		if (OidIsValid(typeOid))
			get_typlenbyval(typeOid, &typLen, &typByVal);
		else
		{
			/* If no type OID, assume by-value, like copyParamList does. */
			typLen = sizeof(Datum);
			typByVal = true;
		}
		sz = add_size(sz,
					  datumEstimateSpace(prm->value, prm->isnull,
										 typByVal, typLen));
	}
	return sz;
}