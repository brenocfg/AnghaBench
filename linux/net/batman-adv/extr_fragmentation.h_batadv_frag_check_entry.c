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
struct batadv_frag_table_entry {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  fragment_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_FRAG_TIMEOUT ; 
 scalar_t__ batadv_has_timed_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
batadv_frag_check_entry(struct batadv_frag_table_entry *frags_entry)
{
	if (!hlist_empty(&frags_entry->fragment_list) &&
	    batadv_has_timed_out(frags_entry->timestamp, BATADV_FRAG_TIMEOUT))
		return true;
	return false;
}