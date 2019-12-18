#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  options; void* serverid; void* userid; int /*<<< orphan*/  umid; } ;
typedef  TYPE_1__ UserMapping ;
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_user_mapping ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_user_mapping_umoptions ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 void* InvalidOid ; 
 int /*<<< orphan*/  MappingUserName (void*) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  ObjectIdGetDatum (void*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  USERMAPPINGUSERSERVER ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  untransformRelOptions (int /*<<< orphan*/ ) ; 

UserMapping *
GetUserMapping(Oid userid, Oid serverid)
{
	Datum		datum;
	HeapTuple	tp;
	bool		isnull;
	UserMapping *um;

	tp = SearchSysCache2(USERMAPPINGUSERSERVER,
						 ObjectIdGetDatum(userid),
						 ObjectIdGetDatum(serverid));

	if (!HeapTupleIsValid(tp))
	{
		/* Not found for the specific user -- try PUBLIC */
		tp = SearchSysCache2(USERMAPPINGUSERSERVER,
							 ObjectIdGetDatum(InvalidOid),
							 ObjectIdGetDatum(serverid));
	}

	if (!HeapTupleIsValid(tp))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("user mapping not found for \"%s\"",
						MappingUserName(userid))));

	um = (UserMapping *) palloc(sizeof(UserMapping));
	um->umid = ((Form_pg_user_mapping) GETSTRUCT(tp))->oid;
	um->userid = userid;
	um->serverid = serverid;

	/* Extract the umoptions */
	datum = SysCacheGetAttr(USERMAPPINGUSERSERVER,
							tp,
							Anum_pg_user_mapping_umoptions,
							&isnull);
	if (isnull)
		um->options = NIL;
	else
		um->options = untransformRelOptions(datum);

	ReleaseSysCache(tp);

	return um;
}