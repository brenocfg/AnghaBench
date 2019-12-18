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
typedef  int /*<<< orphan*/  u64 ;
struct super_block {int dummy; } ;
typedef  void squashfs_page_actor ;

/* Variables and functions */
 int ENOMEM ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int SQUASHFS_COMPRESSED_BIT_BLOCK ; 
 void** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* squashfs_page_actor_init (void**,int,int) ; 
 int squashfs_read_data (struct super_block*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,void*) ; 

void *squashfs_read_table(struct super_block *sb, u64 block, int length)
{
	int pages = (length + PAGE_SIZE - 1) >> PAGE_SHIFT;
	int i, res;
	void *table, *buffer, **data;
	struct squashfs_page_actor *actor;

	table = buffer = kmalloc(length, GFP_KERNEL);
	if (table == NULL)
		return ERR_PTR(-ENOMEM);

	data = kcalloc(pages, sizeof(void *), GFP_KERNEL);
	if (data == NULL) {
		res = -ENOMEM;
		goto failed;
	}

	actor = squashfs_page_actor_init(data, pages, length);
	if (actor == NULL) {
		res = -ENOMEM;
		goto failed2;
	}

	for (i = 0; i < pages; i++, buffer += PAGE_SIZE)
		data[i] = buffer;

	res = squashfs_read_data(sb, block, length |
		SQUASHFS_COMPRESSED_BIT_BLOCK, NULL, actor);

	kfree(data);
	kfree(actor);

	if (res < 0)
		goto failed;

	return table;

failed2:
	kfree(data);
failed:
	kfree(table);
	return ERR_PTR(res);
}