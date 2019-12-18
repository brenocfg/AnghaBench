#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
typedef  int int16 ;
struct TYPE_8__ {int ptype; int pflags; int /*<<< orphan*/  isnull; int /*<<< orphan*/  value; } ;
struct TYPE_7__ {int numParams; TYPE_2__* params; TYPE_2__* (* paramFetch ) (TYPE_1__*,int,int,TYPE_2__*) ;} ;
typedef  TYPE_1__* ParamListInfo ;
typedef  TYPE_2__ ParamExternData ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ OidIsValid (int) ; 
 int /*<<< orphan*/  datumSerialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char**) ; 
 int /*<<< orphan*/  get_typlenbyval (int,int*,int*) ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 
 TYPE_2__* stub1 (TYPE_1__*,int,int,TYPE_2__*) ; 

void
SerializeParamList(ParamListInfo paramLI, char **start_address)
{
	int			nparams;
	int			i;

	/* Write number of parameters. */
	if (paramLI == NULL || paramLI->numParams <= 0)
		nparams = 0;
	else
		nparams = paramLI->numParams;
	memcpy(*start_address, &nparams, sizeof(int));
	*start_address += sizeof(int);

	/* Write each parameter in turn. */
	for (i = 0; i < nparams; i++)
	{
		ParamExternData *prm;
		ParamExternData prmdata;
		Oid			typeOid;
		int16		typLen;
		bool		typByVal;

		/* give hook a chance in case parameter is dynamic */
		if (paramLI->paramFetch != NULL)
			prm = paramLI->paramFetch(paramLI, i + 1, false, &prmdata);
		else
			prm = &paramLI->params[i];

		typeOid = prm->ptype;

		/* Write type OID. */
		memcpy(*start_address, &typeOid, sizeof(Oid));
		*start_address += sizeof(Oid);

		/* Write flags. */
		memcpy(*start_address, &prm->pflags, sizeof(uint16));
		*start_address += sizeof(uint16);

		/* Write datum/isnull. */
		if (OidIsValid(typeOid))
			get_typlenbyval(typeOid, &typLen, &typByVal);
		else
		{
			/* If no type OID, assume by-value, like copyParamList does. */
			typLen = sizeof(Datum);
			typByVal = true;
		}
		datumSerialize(prm->value, prm->isnull, typByVal, typLen,
					   start_address);
	}
}