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
struct log_entry {scalar_t__ lba; scalar_t__ old_map; scalar_t__ new_map; scalar_t__ seq; } ;

/* Variables and functions */

__attribute__((used)) static bool ent_is_padding(struct log_entry *ent)
{
	return (ent->lba == 0) && (ent->old_map == 0) && (ent->new_map == 0)
		&& (ent->seq == 0);
}