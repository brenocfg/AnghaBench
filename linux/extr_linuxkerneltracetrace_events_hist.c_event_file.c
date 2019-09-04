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
struct trace_event_file {int dummy; } ;
struct trace_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct trace_event_file* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct trace_event_file* __find_event_file (struct trace_array*,char*,char*) ; 

__attribute__((used)) static struct trace_event_file *event_file(struct trace_array *tr,
					   char *system, char *event_name)
{
	struct trace_event_file *file;

	file = __find_event_file(tr, system, event_name);
	if (!file)
		return ERR_PTR(-EINVAL);

	return file;
}