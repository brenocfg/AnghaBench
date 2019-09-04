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
struct perf_hpp_list {int dummy; } ;
struct c2c_fmt {int /*<<< orphan*/  fmt; } ;

/* Variables and functions */
 struct c2c_fmt* get_format (char*) ; 
 int output_field_add (struct perf_hpp_list*,char*) ; 
 int /*<<< orphan*/  perf_hpp_list__column_register (struct perf_hpp_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_dimensions () ; 

__attribute__((used)) static int c2c_hists__init_output(struct perf_hpp_list *hpp_list, char *name)
{
	struct c2c_fmt *c2c_fmt = get_format(name);

	if (!c2c_fmt) {
		reset_dimensions();
		return output_field_add(hpp_list, name);
	}

	perf_hpp_list__column_register(hpp_list, &c2c_fmt->fmt);
	return 0;
}