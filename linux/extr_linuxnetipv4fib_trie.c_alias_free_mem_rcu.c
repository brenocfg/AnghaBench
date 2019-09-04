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
struct fib_alias {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  __alias_free_mem ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void alias_free_mem_rcu(struct fib_alias *fa)
{
	call_rcu(&fa->rcu, __alias_free_mem);
}