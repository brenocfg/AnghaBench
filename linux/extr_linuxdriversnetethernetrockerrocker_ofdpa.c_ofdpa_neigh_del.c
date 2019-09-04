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
struct ofdpa_neigh_tbl_entry {scalar_t__ ref_count; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ofdpa_neigh_tbl_entry*) ; 

__attribute__((used)) static void ofdpa_neigh_del(struct ofdpa_neigh_tbl_entry *entry)
{
	if (--entry->ref_count == 0) {
		hash_del(&entry->entry);
		kfree(entry);
	}
}