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
struct perf_gtk_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_gtk__is_active_context (struct perf_gtk_context*) ; 
 int /*<<< orphan*/  zfree (struct perf_gtk_context**) ; 

int perf_gtk__deactivate_context(struct perf_gtk_context **ctx)
{
	if (!perf_gtk__is_active_context(*ctx))
		return -1;

	zfree(ctx);
	return 0;
}