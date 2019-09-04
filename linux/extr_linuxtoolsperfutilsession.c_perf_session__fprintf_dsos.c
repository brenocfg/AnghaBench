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
struct perf_session {int /*<<< orphan*/  machines; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t machines__fprintf_dsos (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

size_t perf_session__fprintf_dsos(struct perf_session *session, FILE *fp)
{
	return machines__fprintf_dsos(&session->machines, fp);
}