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
struct hists {int /*<<< orphan*/  entries_collapsed; int /*<<< orphan*/ * entries_in_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  hists__delete_entries (struct hists*) ; 
 int /*<<< orphan*/  hists__delete_remaining_entries (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hists__delete_all_entries(struct hists *hists)
{
	hists__delete_entries(hists);
	hists__delete_remaining_entries(&hists->entries_in_array[0]);
	hists__delete_remaining_entries(&hists->entries_in_array[1]);
	hists__delete_remaining_entries(&hists->entries_collapsed);
}