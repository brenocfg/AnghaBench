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
typedef  scalar_t__ u16 ;
struct batadv_frag_table_entry {scalar_t__ seqno; scalar_t__ size; int /*<<< orphan*/  fragment_list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_frag_clear_chain (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool batadv_frag_init_chain(struct batadv_frag_table_entry *chain,
				   u16 seqno)
{
	lockdep_assert_held(&chain->lock);

	if (chain->seqno == seqno)
		return false;

	if (!hlist_empty(&chain->fragment_list))
		batadv_frag_clear_chain(&chain->fragment_list, true);

	chain->size = 0;
	chain->seqno = seqno;

	return true;
}