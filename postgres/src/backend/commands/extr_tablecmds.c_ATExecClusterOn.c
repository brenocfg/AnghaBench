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
struct TYPE_8__ {TYPE_1__* rd_rel; } ;
struct TYPE_7__ {int /*<<< orphan*/  relnamespace; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  check_index_is_clusterable (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_relname_relid (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_index_clustered (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ObjectAddress
ATExecClusterOn(Relation rel, const char *indexName, LOCKMODE lockmode)
{
	Oid			indexOid;
	ObjectAddress address;

	indexOid = get_relname_relid(indexName, rel->rd_rel->relnamespace);

	if (!OidIsValid(indexOid))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("index \"%s\" for table \"%s\" does not exist",
						indexName, RelationGetRelationName(rel))));

	/* Check index is valid to cluster on */
	check_index_is_clusterable(rel, indexOid, false, lockmode);

	/* And do the work */
	mark_index_clustered(rel, indexOid, false);

	ObjectAddressSet(address,
					 RelationRelationId, indexOid);

	return address;
}