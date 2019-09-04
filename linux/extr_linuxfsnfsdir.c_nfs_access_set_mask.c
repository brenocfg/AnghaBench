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
typedef  int /*<<< orphan*/  u32 ;
struct nfs_access_entry {int /*<<< orphan*/  mask; } ;

/* Variables and functions */

void nfs_access_set_mask(struct nfs_access_entry *entry, u32 access_result)
{
	entry->mask = access_result;
}