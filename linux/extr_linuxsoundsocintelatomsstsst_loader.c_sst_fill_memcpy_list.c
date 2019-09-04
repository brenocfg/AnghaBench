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
typedef  int /*<<< orphan*/  u32 ;
struct sst_memcpy_list {int is_io; int /*<<< orphan*/  memcpylist; int /*<<< orphan*/  size; void const* src; void* dstn; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sst_memcpy_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static int sst_fill_memcpy_list(struct list_head *memcpy_list,
			void *destn, const void *src, u32 size, bool is_io)
{
	struct sst_memcpy_list *listnode;

	listnode = kzalloc(sizeof(*listnode), GFP_KERNEL);
	if (listnode == NULL)
		return -ENOMEM;
	listnode->dstn = destn;
	listnode->src = src;
	listnode->size = size;
	listnode->is_io = is_io;
	list_add_tail(&listnode->memcpylist, memcpy_list);

	return 0;
}