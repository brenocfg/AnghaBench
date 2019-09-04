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
struct gcov_iterator {int /*<<< orphan*/ * buffer; int /*<<< orphan*/  size; struct gcov_info* info; } ;
struct gcov_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  convert_to_gcda (int /*<<< orphan*/ *,struct gcov_info*) ; 
 int /*<<< orphan*/  kfree (struct gcov_iterator*) ; 
 struct gcov_iterator* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmalloc (int /*<<< orphan*/ ) ; 

struct gcov_iterator *gcov_iter_new(struct gcov_info *info)
{
	struct gcov_iterator *iter;

	iter = kzalloc(sizeof(struct gcov_iterator), GFP_KERNEL);
	if (!iter)
		goto err_free;

	iter->info = info;
	/* Dry-run to get the actual buffer size. */
	iter->size = convert_to_gcda(NULL, info);
	iter->buffer = vmalloc(iter->size);
	if (!iter->buffer)
		goto err_free;

	convert_to_gcda(iter->buffer, info);

	return iter;

err_free:
	kfree(iter);
	return NULL;
}