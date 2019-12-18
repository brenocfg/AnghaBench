#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  serverid; } ;
struct TYPE_10__ {int /*<<< orphan*/  oid; } ;
struct TYPE_9__ {int /*<<< orphan*/  oid; } ;
struct TYPE_8__ {int /*<<< orphan*/  objectId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_user_mapping ;
typedef  TYPE_3__* Form_pg_authid ;
typedef  TYPE_4__ ForeignServer ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHNAME ; 
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 TYPE_4__* GetForeignServerByName (char*,int) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ObjectAddressSet (TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USERMAPPINGUSERSERVER ; 
 int /*<<< orphan*/  UserMappingRelationId ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,...) ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsecond (int /*<<< orphan*/ *) ; 
 char* strVal (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static ObjectAddress
get_object_address_usermapping(List *object, bool missing_ok)
{
	ObjectAddress address;
	Oid			userid;
	char	   *username;
	char	   *servername;
	ForeignServer *server;
	HeapTuple	tp;

	ObjectAddressSet(address, UserMappingRelationId, InvalidOid);

	/* fetch string names from input lists, for error messages */
	username = strVal(linitial(object));
	servername = strVal(lsecond(object));

	/* look up pg_authid OID of mapped user; InvalidOid if PUBLIC */
	if (strcmp(username, "public") == 0)
		userid = InvalidOid;
	else
	{
		tp = SearchSysCache1(AUTHNAME,
							 CStringGetDatum(username));
		if (!HeapTupleIsValid(tp))
		{
			if (!missing_ok)
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_OBJECT),
						 errmsg("user mapping for user \"%s\" on server \"%s\" does not exist",
								username, servername)));
			return address;
		}
		userid = ((Form_pg_authid) GETSTRUCT(tp))->oid;
		ReleaseSysCache(tp);
	}

	/* Now look up the pg_user_mapping tuple */
	server = GetForeignServerByName(servername, true);
	if (!server)
	{
		if (!missing_ok)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("server \"%s\" does not exist", servername)));
		return address;
	}
	tp = SearchSysCache2(USERMAPPINGUSERSERVER,
						 ObjectIdGetDatum(userid),
						 ObjectIdGetDatum(server->serverid));
	if (!HeapTupleIsValid(tp))
	{
		if (!missing_ok)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("user mapping for user \"%s\" on server \"%s\" does not exist",
							username, servername)));
		return address;
	}

	address.objectId = ((Form_pg_user_mapping) GETSTRUCT(tp))->oid;

	ReleaseSysCache(tp);

	return address;
}