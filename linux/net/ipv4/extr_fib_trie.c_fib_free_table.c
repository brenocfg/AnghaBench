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
struct fib_table {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  __trie_free_rcu ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void fib_free_table(struct fib_table *tb)
{
	call_rcu(&tb->rcu, __trie_free_rcu);
}