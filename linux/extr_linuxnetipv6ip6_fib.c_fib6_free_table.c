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
struct fib6_table {int /*<<< orphan*/  tb6_peers; } ;

/* Variables and functions */
 int /*<<< orphan*/  inetpeer_invalidate_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct fib6_table*) ; 

__attribute__((used)) static void fib6_free_table(struct fib6_table *table)
{
	inetpeer_invalidate_tree(&table->tb6_peers);
	kfree(table);
}