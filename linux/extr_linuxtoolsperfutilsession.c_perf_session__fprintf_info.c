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
struct perf_session {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  perf_header__fprintf_info (struct perf_session*,int /*<<< orphan*/ *,int) ; 

void perf_session__fprintf_info(struct perf_session *session, FILE *fp,
				bool full)
{
	if (session == NULL || fp == NULL)
		return;

	fprintf(fp, "# ========\n");
	perf_header__fprintf_info(session, fp, full);
	fprintf(fp, "# ========\n#\n");
}