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
struct tracepoint_path {int /*<<< orphan*/  system; int /*<<< orphan*/  name; struct tracepoint_path* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tracepoint_path*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
put_tracepoints_path(struct tracepoint_path *tps)
{
	while (tps) {
		struct tracepoint_path *t = tps;

		tps = tps->next;
		zfree(&t->name);
		zfree(&t->system);
		free(t);
	}
}