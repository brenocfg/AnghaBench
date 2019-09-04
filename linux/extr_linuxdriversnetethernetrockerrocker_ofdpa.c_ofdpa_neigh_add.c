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
struct ofdpa_neigh_tbl_entry {int /*<<< orphan*/  ip_addr; int /*<<< orphan*/  entry; int /*<<< orphan*/  ref_count; scalar_t__ index; } ;
struct ofdpa {int /*<<< orphan*/  neigh_tbl; int /*<<< orphan*/  neigh_tbl_next_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ofdpa_neigh_add(struct ofdpa *ofdpa,
			    struct ofdpa_neigh_tbl_entry *entry)
{
	entry->index = ofdpa->neigh_tbl_next_index++;
	entry->ref_count++;
	hash_add(ofdpa->neigh_tbl, &entry->entry,
		 be32_to_cpu(entry->ip_addr));
}