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
struct ebt_entry_target {int dummy; } ;
struct ebt_entry {int dummy; } ;

/* Variables and functions */
 struct ebt_entry_target const* ebt_get_target (struct ebt_entry*) ; 

__attribute__((used)) static inline const struct ebt_entry_target *
ebt_get_target_c(const struct ebt_entry *e)
{
	return ebt_get_target((struct ebt_entry *)e);
}