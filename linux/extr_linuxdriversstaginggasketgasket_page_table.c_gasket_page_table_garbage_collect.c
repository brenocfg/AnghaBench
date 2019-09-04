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
struct gasket_page_table {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  gasket_page_table_garbage_collect_nolock (struct gasket_page_table*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void gasket_page_table_garbage_collect(struct gasket_page_table *pg_tbl)
{
	mutex_lock(&pg_tbl->mutex);
	gasket_page_table_garbage_collect_nolock(pg_tbl);
	mutex_unlock(&pg_tbl->mutex);
}