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
struct pgv {int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages (unsigned long,unsigned int) ; 
 scalar_t__ is_vmalloc_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pgv*) ; 
 scalar_t__ likely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_pg_vec(struct pgv *pg_vec, unsigned int order,
			unsigned int len)
{
	int i;

	for (i = 0; i < len; i++) {
		if (likely(pg_vec[i].buffer)) {
			if (is_vmalloc_addr(pg_vec[i].buffer))
				vfree(pg_vec[i].buffer);
			else
				free_pages((unsigned long)pg_vec[i].buffer,
					   order);
			pg_vec[i].buffer = NULL;
		}
	}
	kfree(pg_vec);
}