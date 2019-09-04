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
struct perf_hpp_fmt {int dummy; } ;
struct perf_hpp {int /*<<< orphan*/  size; int /*<<< orphan*/  buf; } ;
struct hist_entry {int /*<<< orphan*/  hists; } ;

/* Variables and functions */
 int c2c_width (struct perf_hpp_fmt*,struct perf_hpp*,int /*<<< orphan*/ ) ; 
 int scnprintf (char*,int,char*,int,...) ; 

__attribute__((used)) static int
mean_entry(struct perf_hpp_fmt *fmt, struct perf_hpp *hpp,
	   struct hist_entry *he, double mean)
{
	int width = c2c_width(fmt, hpp, he->hists);
	char buf[10];

	scnprintf(buf, 10, "%6.0f", mean);
	return scnprintf(hpp->buf, hpp->size, "%*s", width, buf);
}