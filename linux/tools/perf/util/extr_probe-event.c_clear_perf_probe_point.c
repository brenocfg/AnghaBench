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
struct perf_probe_point {int /*<<< orphan*/  lazy_line; int /*<<< orphan*/  function; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_perf_probe_point(struct perf_probe_point *pp)
{
	zfree(&pp->file);
	zfree(&pp->function);
	zfree(&pp->lazy_line);
}