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
struct perf_probe_event {int uprobes; int /*<<< orphan*/  target; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static int
prog_config__module(const char *value, struct perf_probe_event *pev)
{
	pev->uprobes = false;
	pev->target = strdup(value);
	if (!pev->target)
		return -ENOMEM;
	return 0;
}