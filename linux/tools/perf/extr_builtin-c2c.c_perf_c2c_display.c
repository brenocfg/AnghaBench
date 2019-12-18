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

/* Variables and functions */
 int /*<<< orphan*/  perf_c2c__hists_fprintf (int /*<<< orphan*/ ,struct perf_session*) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ use_browser ; 

__attribute__((used)) static void perf_c2c_display(struct perf_session *session)
{
	use_browser = 0;
	perf_c2c__hists_fprintf(stdout, session);
}