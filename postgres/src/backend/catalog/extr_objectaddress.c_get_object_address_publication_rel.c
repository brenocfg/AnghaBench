#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  objectId; } ;
struct TYPE_6__ {int /*<<< orphan*/  oid; } ;
typedef  scalar_t__ Relation ;
typedef  TYPE_1__ Publication ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_publication_rel_oid ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* GetPublicationByName (char*,int) ; 
 int /*<<< orphan*/  GetSysCacheOid2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ObjectAddressSet (TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUBLICATIONRELMAP ; 
 int /*<<< orphan*/  PublicationRelRelationId ; 
 int /*<<< orphan*/  RelationGetRelationName (scalar_t__) ; 
 int /*<<< orphan*/  RelationGetRelid (scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * linitial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsecond (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makeRangeVarFromNameList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  relation_close (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ relation_openrv_extended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* strVal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ObjectAddress
get_object_address_publication_rel(List *object,
								   Relation *relp, bool missing_ok)
{
	ObjectAddress address;
	Relation	relation;
	List	   *relname;
	char	   *pubname;
	Publication *pub;

	ObjectAddressSet(address, PublicationRelRelationId, InvalidOid);

	relname = linitial(object);
	relation = relation_openrv_extended(makeRangeVarFromNameList(relname),
										AccessShareLock, missing_ok);
	if (!relation)
		return address;

	/* fetch publication name from input list */
	pubname = strVal(lsecond(object));

	/* Now look up the pg_publication tuple */
	pub = GetPublicationByName(pubname, missing_ok);
	if (!pub)
	{
		relation_close(relation, AccessShareLock);
		return address;
	}

	/* Find the publication relation mapping in syscache. */
	address.objectId =
		GetSysCacheOid2(PUBLICATIONRELMAP, Anum_pg_publication_rel_oid,
						ObjectIdGetDatum(RelationGetRelid(relation)),
						ObjectIdGetDatum(pub->oid));
	if (!OidIsValid(address.objectId))
	{
		if (!missing_ok)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("publication relation \"%s\" in publication \"%s\" does not exist",
							RelationGetRelationName(relation), pubname)));
		relation_close(relation, AccessShareLock);
		return address;
	}

	*relp = relation;
	return address;
}