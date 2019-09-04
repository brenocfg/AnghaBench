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
struct hists {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dso_list; int /*<<< orphan*/  field_sep; int /*<<< orphan*/  col_width_list_str; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 unsigned int const hists__col_len (struct hists*,int) ; 
 int /*<<< orphan*/  hists__set_col_len (struct hists*,int,unsigned int const) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static void hists__set_unres_dso_col_len(struct hists *hists, int dso)
{
	const unsigned int unresolved_col_width = BITS_PER_LONG / 4;

	if (hists__col_len(hists, dso) < unresolved_col_width &&
	    !symbol_conf.col_width_list_str && !symbol_conf.field_sep &&
	    !symbol_conf.dso_list)
		hists__set_col_len(hists, dso, unresolved_col_width);
}