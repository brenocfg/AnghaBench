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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BOOTSTRAP_SUPERUSERID ; 
 int /*<<< orphan*/  COLLPROVIDER_LIBC ; 
 int /*<<< orphan*/  PG_CMD_PRINTF (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_CMD_PUTS (char*) ; 
 int /*<<< orphan*/  PG_UTF8 ; 

__attribute__((used)) static void
setup_collation(FILE *cmdfd)
{
	/*
	 * Add an SQL-standard name.  We don't want to pin this, so it doesn't go
	 * in pg_collation.h.  But add it before reading system collations, so
	 * that it wins if libc defines a locale named ucs_basic.
	 */
	PG_CMD_PRINTF("INSERT INTO pg_collation (oid, collname, collnamespace, collowner, collprovider, collisdeterministic, collencoding, collcollate, collctype)"
				   "VALUES (pg_nextoid('pg_catalog.pg_collation', 'oid', 'pg_catalog.pg_collation_oid_index'), 'ucs_basic', 'pg_catalog'::regnamespace, %u, '%c', true, %d, 'C', 'C');\n\n",
				   BOOTSTRAP_SUPERUSERID, COLLPROVIDER_LIBC, PG_UTF8);

	/* Now import all collations we can find in the operating system */
	PG_CMD_PUTS("SELECT pg_import_system_collations('pg_catalog');\n\n");
}