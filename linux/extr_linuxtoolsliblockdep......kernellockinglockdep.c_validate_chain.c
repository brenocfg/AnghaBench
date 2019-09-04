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
typedef  int /*<<< orphan*/  u64 ;
struct task_struct {int dummy; } ;
struct lockdep_map {int dummy; } ;
struct held_lock {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int validate_chain(struct task_struct *curr,
	       	struct lockdep_map *lock, struct held_lock *hlock,
		int chain_head, u64 chain_key)
{
	return 1;
}