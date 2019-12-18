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
typedef  int u8 ;
struct batadv_tt_common_entry {int flags; } ;

/* Variables and functions */
 int BATADV_TT_CLIENT_NEW ; 

__attribute__((used)) static bool batadv_tt_local_valid(const void *entry_ptr,
				  const void *data_ptr,
				  u8 *flags)
{
	const struct batadv_tt_common_entry *tt_common_entry = entry_ptr;

	if (tt_common_entry->flags & BATADV_TT_CLIENT_NEW)
		return false;

	if (flags)
		*flags = tt_common_entry->flags;

	return true;
}