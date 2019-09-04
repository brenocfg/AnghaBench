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
struct perf_hpp_fmt {int len; scalar_t__ user_len; } ;
struct perf_hpp {int dummy; } ;
struct hist_entry {int dummy; } ;
typedef  int /*<<< orphan*/  hpp_snprint_fn ;
typedef  int /*<<< orphan*/  hpp_field_fn ;
struct TYPE_2__ {scalar_t__ field_sep; } ;

/* Variables and functions */
 int __hpp__fmt (struct perf_hpp*,struct hist_entry*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ symbol_conf ; 

int hpp__fmt(struct perf_hpp_fmt *fmt, struct perf_hpp *hpp,
	     struct hist_entry *he, hpp_field_fn get_field,
	     const char *fmtstr, hpp_snprint_fn print_fn, bool fmt_percent)
{
	int len = fmt->user_len ?: fmt->len;

	if (symbol_conf.field_sep) {
		return __hpp__fmt(hpp, he, get_field, fmtstr, 1,
				  print_fn, fmt_percent);
	}

	if (fmt_percent)
		len -= 2; /* 2 for a space and a % sign */
	else
		len -= 1;

	return  __hpp__fmt(hpp, he, get_field, fmtstr, len, print_fn, fmt_percent);
}