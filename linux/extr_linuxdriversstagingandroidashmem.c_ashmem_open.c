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
struct inode {int dummy; } ;
struct file {struct ashmem_area* private_data; } ;
struct ashmem_area {int /*<<< orphan*/  prot_mask; int /*<<< orphan*/  name; int /*<<< orphan*/  unpinned_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASHMEM_NAME_PREFIX ; 
 int /*<<< orphan*/  ASHMEM_NAME_PREFIX_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROT_MASK ; 
 int /*<<< orphan*/  ashmem_area_cachep ; 
 int generic_file_open (struct inode*,struct file*) ; 
 struct ashmem_area* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ashmem_open(struct inode *inode, struct file *file)
{
	struct ashmem_area *asma;
	int ret;

	ret = generic_file_open(inode, file);
	if (ret)
		return ret;

	asma = kmem_cache_zalloc(ashmem_area_cachep, GFP_KERNEL);
	if (!asma)
		return -ENOMEM;

	INIT_LIST_HEAD(&asma->unpinned_list);
	memcpy(asma->name, ASHMEM_NAME_PREFIX, ASHMEM_NAME_PREFIX_LEN);
	asma->prot_mask = PROT_MASK;
	file->private_data = asma;

	return 0;
}