#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  connection; } ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
die_on_query_failure(ArchiveHandle *AH, const char *query)
{
	pg_log_error("query failed: %s",
				 PQerrorMessage(AH->connection));
	fatal("query was: %s", query);
}