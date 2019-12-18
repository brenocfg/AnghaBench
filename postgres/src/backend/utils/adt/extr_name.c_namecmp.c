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
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * Name ;

/* Variables and functions */
 scalar_t__ C_COLLATION_OID ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int varstr_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
namecmp(Name arg1, Name arg2, Oid collid)
{
	/* Fast path for common case used in system catalogs */
	if (collid == C_COLLATION_OID)
		return strncmp(NameStr(*arg1), NameStr(*arg2), NAMEDATALEN);

	/* Else rely on the varstr infrastructure */
	return varstr_cmp(NameStr(*arg1), strlen(NameStr(*arg1)),
					  NameStr(*arg2), strlen(NameStr(*arg2)),
					  collid);
}