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
 int /*<<< orphan*/  dso__missing_buildid_cache ; 
 int /*<<< orphan*/  perf_session__fprintf_dsos_buildid (struct perf_session*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_id_cache__fprintf_missing(struct perf_session *session, FILE *fp)
{
	perf_session__fprintf_dsos_buildid(session, fp, dso__missing_buildid_cache, 0);
	return 0;
}