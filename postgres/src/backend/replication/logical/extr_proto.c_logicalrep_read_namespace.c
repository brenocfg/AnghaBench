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

/* Variables and functions */
 char* pq_getmsgstring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
logicalrep_read_namespace(StringInfo in)
{
	const char *nspname = pq_getmsgstring(in);

	if (nspname[0] == '\0')
		nspname = "pg_catalog";

	return nspname;
}