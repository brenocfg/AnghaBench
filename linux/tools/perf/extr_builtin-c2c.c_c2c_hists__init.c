#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nr_header_lines; } ;
struct c2c_hists {TYPE_1__ list; int /*<<< orphan*/  hists; } ;

/* Variables and functions */
 int /*<<< orphan*/  __hists__init (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int hpp_list__parse (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  perf_hpp_list__init (TYPE_1__*) ; 

__attribute__((used)) static int c2c_hists__init(struct c2c_hists *hists,
			   const char *sort,
			   int nr_header_lines)
{
	__hists__init(&hists->hists, &hists->list);

	/*
	 * Initialize only with sort fields, we need to resort
	 * later anyway, and that's where we add output fields
	 * as well.
	 */
	perf_hpp_list__init(&hists->list);

	/* Overload number of header lines.*/
	hists->list.nr_header_lines = nr_header_lines;

	return hpp_list__parse(&hists->list, NULL, sort);
}