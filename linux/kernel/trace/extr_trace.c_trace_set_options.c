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
struct trace_array {int dummy; } ;

/* Variables and functions */
 int match_string (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int set_tracer_flag (struct trace_array*,int,int) ; 
 int set_tracer_option (struct trace_array*,char*,int) ; 
 int str_has_prefix (char*,char*) ; 
 size_t strlen (char*) ; 
 char* strstrip (char*) ; 
 int /*<<< orphan*/  trace_options ; 
 int /*<<< orphan*/  trace_types_lock ; 

__attribute__((used)) static int trace_set_options(struct trace_array *tr, char *option)
{
	char *cmp;
	int neg = 0;
	int ret;
	size_t orig_len = strlen(option);
	int len;

	cmp = strstrip(option);

	len = str_has_prefix(cmp, "no");
	if (len)
		neg = 1;

	cmp += len;

	mutex_lock(&trace_types_lock);

	ret = match_string(trace_options, -1, cmp);
	/* If no option could be set, test the specific tracer options */
	if (ret < 0)
		ret = set_tracer_option(tr, cmp, neg);
	else
		ret = set_tracer_flag(tr, 1 << ret, !neg);

	mutex_unlock(&trace_types_lock);

	/*
	 * If the first trailing whitespace is replaced with '\0' by strstrip,
	 * turn it back into a space.
	 */
	if (orig_len > strlen(option))
		option[strlen(option)] = ' ';

	return ret;
}