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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int PRETTYFLAG_INDENT ; 
 int PRETTYFLAG_PAREN ; 
 int PRETTYFLAG_SCHEMA ; 
 char* pg_get_indexdef_worker (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,int,int) ; 

char *
pg_get_indexdef_columns(Oid indexrelid, bool pretty)
{
	int			prettyFlags;

	prettyFlags = pretty ? (PRETTYFLAG_PAREN | PRETTYFLAG_INDENT | PRETTYFLAG_SCHEMA) : PRETTYFLAG_INDENT;

	return pg_get_indexdef_worker(indexrelid, 0, NULL,
								  true, true,
								  false, false,
								  prettyFlags, false);
}