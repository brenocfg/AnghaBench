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
struct pfn_array_table {int pat_nr; int /*<<< orphan*/ * pat_pa; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfn_array_unpin_free (int /*<<< orphan*/ *,struct device*) ; 

__attribute__((used)) static void pfn_array_table_unpin_free(struct pfn_array_table *pat,
				       struct device *mdev)
{
	int i;

	for (i = 0; i < pat->pat_nr; i++)
		pfn_array_unpin_free(pat->pat_pa + i, mdev);

	if (pat->pat_nr) {
		kfree(pat->pat_pa);
		pat->pat_pa = NULL;
		pat->pat_nr = 0;
	}
}