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
struct bucket_table {scalar_t__ nest; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (struct bucket_table const*) ; 
 int /*<<< orphan*/  nested_bucket_table_free (struct bucket_table const*) ; 

__attribute__((used)) static void bucket_table_free(const struct bucket_table *tbl)
{
	if (tbl->nest)
		nested_bucket_table_free(tbl);

	kvfree(tbl);
}