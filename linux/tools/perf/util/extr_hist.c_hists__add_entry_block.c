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
struct hists {int dummy; } ;
struct hist_entry {struct hists* hists; struct block_info* block_info; } ;
struct block_info {int dummy; } ;
struct addr_location {int dummy; } ;

/* Variables and functions */
 struct hist_entry* hists__findnew_entry (struct hists*,struct hist_entry*,struct addr_location*,int) ; 

struct hist_entry *hists__add_entry_block(struct hists *hists,
					  struct addr_location *al,
					  struct block_info *block_info)
{
	struct hist_entry entry = {
		.block_info = block_info,
		.hists = hists,
	}, *he = hists__findnew_entry(hists, &entry, al, false);

	return he;
}