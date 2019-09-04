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
struct convert {int /*<<< orphan*/  queue_size; } ;

/* Variables and functions */
 int perf_config_u64 (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int convert__config(const char *var, const char *value, void *cb)
{
	struct convert *c = cb;

	if (!strcmp(var, "convert.queue-size"))
		return perf_config_u64(&c->queue_size, var, value);

	return 0;
}