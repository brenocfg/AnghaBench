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
typedef  enum wimax_st { ____Placeholder_wimax_st } wimax_st ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

__attribute__((used)) static
void __check_new_state(enum wimax_st old_state, enum wimax_st new_state,
		       unsigned int allowed_states_bm)
{
	if (WARN_ON(((1 << new_state) & allowed_states_bm) == 0)) {
		pr_err("SW BUG! Forbidden state change %u -> %u\n",
		       old_state, new_state);
	}
}