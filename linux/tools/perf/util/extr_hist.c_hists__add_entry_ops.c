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
struct symbol {int dummy; } ;
struct perf_sample {int dummy; } ;
struct mem_info {int dummy; } ;
struct hists {int dummy; } ;
struct hist_entry_ops {int dummy; } ;
struct hist_entry {int dummy; } ;
struct branch_info {int dummy; } ;
struct addr_location {int dummy; } ;

/* Variables and functions */
 struct hist_entry* __hists__add_entry (struct hists*,struct addr_location*,struct symbol*,struct branch_info*,struct mem_info*,int /*<<< orphan*/ *,struct perf_sample*,int,struct hist_entry_ops*) ; 

struct hist_entry *hists__add_entry_ops(struct hists *hists,
					struct hist_entry_ops *ops,
					struct addr_location *al,
					struct symbol *sym_parent,
					struct branch_info *bi,
					struct mem_info *mi,
					struct perf_sample *sample,
					bool sample_self)
{
	return __hists__add_entry(hists, al, sym_parent, bi, mi, NULL,
				  sample, sample_self, ops);
}