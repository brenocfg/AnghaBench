#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hist_entry {int /*<<< orphan*/  dummy; } ;
struct TYPE_2__ {scalar_t__ field_sep; } ;

/* Variables and functions */
 double baseline_percent (struct hist_entry*) ; 
 int scnprintf (char*,size_t,char const*,double) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int hpp__entry_baseline(struct hist_entry *he, char *buf, size_t size)
{
	double percent = baseline_percent(he);
	const char *fmt = symbol_conf.field_sep ? "%.2f" : "%6.2f%%";
	int ret = 0;

	if (!he->dummy)
		ret = scnprintf(buf, size, fmt, percent);

	return ret;
}