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
struct gcov_info {int n_functions; struct gcov_ctr_info* counts; int /*<<< orphan*/  functions; int /*<<< orphan*/  filename; int /*<<< orphan*/  ctr_mask; int /*<<< orphan*/  stamp; int /*<<< orphan*/  version; } ;
struct gcov_ctr_info {int num; int /*<<< orphan*/  values; int /*<<< orphan*/  merge; } ;
typedef  int /*<<< orphan*/  gcov_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  counts ; 
 int /*<<< orphan*/  gcov_info_free (struct gcov_info*) ; 
 int get_fn_size (struct gcov_info*) ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gcov_info* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 unsigned int num_counter_active (struct gcov_info*) ; 
 int /*<<< orphan*/  struct_size (struct gcov_info*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  vmalloc (size_t) ; 

struct gcov_info *gcov_info_dup(struct gcov_info *info)
{
	struct gcov_info *dup;
	unsigned int i;
	unsigned int active;

	/* Duplicate gcov_info. */
	active = num_counter_active(info);
	dup = kzalloc(struct_size(dup, counts, active), GFP_KERNEL);
	if (!dup)
		return NULL;
	dup->version		= info->version;
	dup->stamp		= info->stamp;
	dup->n_functions	= info->n_functions;
	dup->ctr_mask		= info->ctr_mask;
	/* Duplicate filename. */
	dup->filename		= kstrdup(info->filename, GFP_KERNEL);
	if (!dup->filename)
		goto err_free;
	/* Duplicate table of functions. */
	dup->functions = kmemdup(info->functions, info->n_functions *
				 get_fn_size(info), GFP_KERNEL);
	if (!dup->functions)
		goto err_free;
	/* Duplicate counter arrays. */
	for (i = 0; i < active ; i++) {
		struct gcov_ctr_info *ctr = &info->counts[i];
		size_t size = ctr->num * sizeof(gcov_type);

		dup->counts[i].num = ctr->num;
		dup->counts[i].merge = ctr->merge;
		dup->counts[i].values = vmalloc(size);
		if (!dup->counts[i].values)
			goto err_free;
		memcpy(dup->counts[i].values, ctr->values, size);
	}
	return dup;

err_free:
	gcov_info_free(dup);
	return NULL;
}