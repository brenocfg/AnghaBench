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
struct TYPE_7__ {TYPE_1__* rd_rel; } ;
struct TYPE_6__ {int /*<<< orphan*/  relnamespace; } ;
typedef  TYPE_2__* Relation ;

/* Variables and functions */
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 scalar_t__ RelationIsVisible (int /*<<< orphan*/ ) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 char* quote_qualified_identifier (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
generate_relation_name(Relation rel)
{
	char	   *nspname;
	char	   *result;

	/* Qualify the name if not visible in search path */
	if (RelationIsVisible(RelationGetRelid(rel)))
		nspname = NULL;
	else
		nspname = get_namespace_name(rel->rd_rel->relnamespace);

	result = quote_qualified_identifier(nspname, RelationGetRelationName(rel));

	return result;
}