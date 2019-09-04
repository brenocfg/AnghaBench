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
struct key {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int KEY_IS_POSITIVE ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mark_key_instantiated(struct key *key, int reject_error)
{
	/* Commit the payload before setting the state; barrier versus
	 * key_read_state().
	 */
	smp_store_release(&key->state,
			  (reject_error < 0) ? reject_error : KEY_IS_POSITIVE);
}