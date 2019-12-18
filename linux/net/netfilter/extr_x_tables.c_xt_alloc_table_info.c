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
struct xt_table_info {unsigned int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 size_t XT_MAX_TABLE_SIZE ; 
 struct xt_table_info* kvmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xt_table_info*,int /*<<< orphan*/ ,int) ; 

struct xt_table_info *xt_alloc_table_info(unsigned int size)
{
	struct xt_table_info *info = NULL;
	size_t sz = sizeof(*info) + size;

	if (sz < sizeof(*info) || sz >= XT_MAX_TABLE_SIZE)
		return NULL;

	info = kvmalloc(sz, GFP_KERNEL_ACCOUNT);
	if (!info)
		return NULL;

	memset(info, 0, sizeof(*info));
	info->size = size;
	return info;
}