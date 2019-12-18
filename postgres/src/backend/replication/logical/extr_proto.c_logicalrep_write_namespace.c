#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  StringInfo ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PG_CATALOG_NAMESPACE ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 char* get_namespace_name (scalar_t__) ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  pq_sendstring (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
logicalrep_write_namespace(StringInfo out, Oid nspid)
{
	if (nspid == PG_CATALOG_NAMESPACE)
		pq_sendbyte(out, '\0');
	else
	{
		char	   *nspname = get_namespace_name(nspid);

		if (nspname == NULL)
			elog(ERROR, "cache lookup failed for namespace %u",
				 nspid);

		pq_sendstring(out, nspname);
	}
}