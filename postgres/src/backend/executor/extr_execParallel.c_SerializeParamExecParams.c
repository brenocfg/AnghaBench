#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int16 ;
typedef  int /*<<< orphan*/  dsa_pointer ;
typedef  int /*<<< orphan*/  dsa_area ;
struct TYPE_8__ {TYPE_1__* es_plannedstmt; TYPE_2__* es_param_exec_vals; } ;
struct TYPE_7__ {int /*<<< orphan*/  isnull; int /*<<< orphan*/  value; } ;
struct TYPE_6__ {int /*<<< orphan*/  paramExecTypes; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_2__ ParamExecData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ EState ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  EstimateParamExecSpace (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int bms_next_member (int /*<<< orphan*/ *,int) ; 
 int bms_num_members (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  datumSerialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char**) ; 
 int /*<<< orphan*/  dsa_allocate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* dsa_get_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_typlenbyval (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  list_nth_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 

__attribute__((used)) static dsa_pointer
SerializeParamExecParams(EState *estate, Bitmapset *params, dsa_area *area)
{
	Size		size;
	int			nparams;
	int			paramid;
	ParamExecData *prm;
	dsa_pointer handle;
	char	   *start_address;

	/* Allocate enough space for the current parameter values. */
	size = EstimateParamExecSpace(estate, params);
	handle = dsa_allocate(area, size);
	start_address = dsa_get_address(area, handle);

	/* First write the number of parameters as a 4-byte integer. */
	nparams = bms_num_members(params);
	memcpy(start_address, &nparams, sizeof(int));
	start_address += sizeof(int);

	/* Write details for each parameter in turn. */
	paramid = -1;
	while ((paramid = bms_next_member(params, paramid)) >= 0)
	{
		Oid			typeOid;
		int16		typLen;
		bool		typByVal;

		prm = &(estate->es_param_exec_vals[paramid]);
		typeOid = list_nth_oid(estate->es_plannedstmt->paramExecTypes,
							   paramid);

		/* Write paramid. */
		memcpy(start_address, &paramid, sizeof(int));
		start_address += sizeof(int);

		/* Write datum/isnull */
		if (OidIsValid(typeOid))
			get_typlenbyval(typeOid, &typLen, &typByVal);
		else
		{
			/* If no type OID, assume by-value, like copyParamList does. */
			typLen = sizeof(Datum);
			typByVal = true;
		}
		datumSerialize(prm->value, prm->isnull, typByVal, typLen,
					   &start_address);
	}

	return handle;
}