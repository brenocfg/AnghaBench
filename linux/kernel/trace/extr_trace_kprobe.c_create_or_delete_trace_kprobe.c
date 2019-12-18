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

/* Variables and functions */
 int ECANCELED ; 
 int EINVAL ; 
 int dyn_event_release (int,char**,int /*<<< orphan*/ *) ; 
 int trace_kprobe_create (int,char const**) ; 
 int /*<<< orphan*/  trace_kprobe_ops ; 

__attribute__((used)) static int create_or_delete_trace_kprobe(int argc, char **argv)
{
	int ret;

	if (argv[0][0] == '-')
		return dyn_event_release(argc, argv, &trace_kprobe_ops);

	ret = trace_kprobe_create(argc, (const char **)argv);
	return ret == -ECANCELED ? -EINVAL : ret;
}