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
struct c2c_hists {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int hpp_list__parse (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  perf_hpp__reset_output_field (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int c2c_hists__reinit(struct c2c_hists *c2c_hists,
			     const char *output,
			     const char *sort)
{
	perf_hpp__reset_output_field(&c2c_hists->list);
	return hpp_list__parse(&c2c_hists->list, output, sort);
}