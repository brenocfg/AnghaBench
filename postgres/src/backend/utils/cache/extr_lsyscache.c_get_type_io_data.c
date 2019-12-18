#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_2__ {int typbyval; char typalign; char typdelim; int /*<<< orphan*/  typsend; int /*<<< orphan*/  typreceive; int /*<<< orphan*/  typoutput; int /*<<< orphan*/  typinput; int /*<<< orphan*/  typlen; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int IOFuncSelector ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_type ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
#define  IOFunc_input 131 
#define  IOFunc_output 130 
#define  IOFunc_receive 129 
#define  IOFunc_send 128 
 scalar_t__ IsBootstrapProcessingMode () ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPEOID ; 
 int /*<<< orphan*/  boot_get_type_io_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  getTypeIOParam (int /*<<< orphan*/ ) ; 

void
get_type_io_data(Oid typid,
				 IOFuncSelector which_func,
				 int16 *typlen,
				 bool *typbyval,
				 char *typalign,
				 char *typdelim,
				 Oid *typioparam,
				 Oid *func)
{
	HeapTuple	typeTuple;
	Form_pg_type typeStruct;

	/*
	 * In bootstrap mode, pass it off to bootstrap.c.  This hack allows us to
	 * use array_in and array_out during bootstrap.
	 */
	if (IsBootstrapProcessingMode())
	{
		Oid			typinput;
		Oid			typoutput;

		boot_get_type_io_data(typid,
							  typlen,
							  typbyval,
							  typalign,
							  typdelim,
							  typioparam,
							  &typinput,
							  &typoutput);
		switch (which_func)
		{
			case IOFunc_input:
				*func = typinput;
				break;
			case IOFunc_output:
				*func = typoutput;
				break;
			default:
				elog(ERROR, "binary I/O not supported during bootstrap");
				break;
		}
		return;
	}

	typeTuple = SearchSysCache1(TYPEOID, ObjectIdGetDatum(typid));
	if (!HeapTupleIsValid(typeTuple))
		elog(ERROR, "cache lookup failed for type %u", typid);
	typeStruct = (Form_pg_type) GETSTRUCT(typeTuple);

	*typlen = typeStruct->typlen;
	*typbyval = typeStruct->typbyval;
	*typalign = typeStruct->typalign;
	*typdelim = typeStruct->typdelim;
	*typioparam = getTypeIOParam(typeTuple);
	switch (which_func)
	{
		case IOFunc_input:
			*func = typeStruct->typinput;
			break;
		case IOFunc_output:
			*func = typeStruct->typoutput;
			break;
		case IOFunc_receive:
			*func = typeStruct->typreceive;
			break;
		case IOFunc_send:
			*func = typeStruct->typsend;
			break;
	}
	ReleaseSysCache(typeTuple);
}