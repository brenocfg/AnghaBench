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
struct hist_entry {int dummy; } ;
struct diff_hpp_fmt {int idx; } ;

/* Variables and functions */
 int PERF_HPP_DIFF__BASELINE ; 
 struct hist_entry* get_pair_fmt (struct hist_entry*,struct diff_hpp_fmt*) ; 
 int /*<<< orphan*/  hpp__entry_baseline (struct hist_entry*,char*,size_t) ; 
 int /*<<< orphan*/  hpp__entry_pair (struct hist_entry*,struct hist_entry*,int,char*,size_t) ; 
 int /*<<< orphan*/  hpp__entry_unpair (struct hist_entry*,int,char*,size_t) ; 

__attribute__((used)) static void
__hpp__entry_global(struct hist_entry *he, struct diff_hpp_fmt *dfmt,
		    char *buf, size_t size)
{
	struct hist_entry *pair = get_pair_fmt(he, dfmt);
	int idx = dfmt->idx;

	/* baseline is special */
	if (idx == PERF_HPP_DIFF__BASELINE)
		hpp__entry_baseline(he, buf, size);
	else {
		if (pair)
			hpp__entry_pair(he, pair, idx, buf, size);
		else
			hpp__entry_unpair(he, idx, buf, size);
	}
}