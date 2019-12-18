#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  host; } ;
struct perf_session {TYPE_1__ machines; } ;

/* Variables and functions */
 int /*<<< orphan*/  machine__delete_threads (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void perf_session__delete_threads(struct perf_session *session)
{
	machine__delete_threads(&session->machines.host);
}