#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* rd_rel; } ;
struct TYPE_8__ {char relreplident; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_2__* Relation ;

/* Variables and functions */
 int /*<<< orphan*/  RelationGetNamespace (TYPE_2__*) ; 
 char* RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  logicalrep_write_attrs (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  logicalrep_write_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendstring (int /*<<< orphan*/ ,char*) ; 

void
logicalrep_write_rel(StringInfo out, Relation rel)
{
	char	   *relname;

	pq_sendbyte(out, 'R');		/* sending RELATION */

	/* use Oid as relation identifier */
	pq_sendint32(out, RelationGetRelid(rel));

	/* send qualified relation name */
	logicalrep_write_namespace(out, RelationGetNamespace(rel));
	relname = RelationGetRelationName(rel);
	pq_sendstring(out, relname);

	/* send replica identity */
	pq_sendbyte(out, rel->rd_rel->relreplident);

	/* send the attribute info */
	logicalrep_write_attrs(out, rel);
}